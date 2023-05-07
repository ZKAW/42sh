/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** exec
*/

#include "mysh.h"

void teach_child(char* path, char** cmd, shell_t* shell)
{
    if (execve(path, cmd, shell->envp) == -1) {
        handle_child_error(cmd);
    }
}

void run_command(cmd_t* cmd, shell_t* shell)
{
    int fd[2];
    char* path = cmd->argv[0];
    char *full_path = get_full_path(cmd->argv[0], shell);

    if (full_path)
        path = full_path;
    if (!is_builtin(cmd->argv[0]) && not_existing(path, shell)) {
        exit(1);
        return;
    }
    if (is_builtin(cmd->argv[0])) {
        run_builtin(cmd, shell);
        exit(shell->state);
    } else {
        if (cmd->input_type != NONE)
            set_input(cmd, shell, fd);
        if (cmd->output_type != NONE)
            set_output(cmd);
        teach_child(path, cmd->argv, shell);
    }
}

void handle_sigchld(int signo) {
    (void)signo;
}

// TODO: fix second pipe not getting executed
/*
ls | cat -e
-> cat -e is not executed
*/
void prepare_pipe(cmd_t* cmd, shell_t* shell, int fd[2]) {
    pid_t new_sub = fork();

    if (new_sub == 0) {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        run_command(cmd->next, shell);
        // exit(shell->state);
        return;
    }

    fcntl(fd[0], F_SETFL, O_NONBLOCK);
    signal(SIGCHLD, handle_sigchld);

    // read from the pipe until the child process has exited
    while (waitpid(new_sub, &shell->state, WNOHANG) == 0) {
        char buf[1024];
        int n = read(fd[0], buf, sizeof(buf));
        if (n > 0) {
            write(1, buf, n);
        }
    }

    // restore the default signal handler
    signal(SIGCHLD, SIG_DFL);

    handle_status(shell, cmd);
    SHARED_STATUS = shell->state;
    close(fd[0]);
    close(fd[1]);
}

void execute(cmd_t* cmd, shell_t* shell)
{
    pid_t sub = fork();

    if (sub == 0) {
        shell->sub = getpid();
        run_command(cmd, shell);
        return;
    }
    waitpid(sub, &shell->state, 0);
    handle_status(shell, cmd);
    if (shell->state == 0 && cmd->input_type == PIPE)
        return;
    SHARED_STATUS = shell->state;
}
