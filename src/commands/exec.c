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

void run_command(cmd_t* cmd, shell_t* shell, int output_fd[2])
{
    int input_fd[2];
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
        if (cmd->output_type != NONE)
            set_output(cmd, output_fd);
        if (cmd->input_type != NONE)
            set_input(cmd, shell, input_fd);
        teach_child(path, cmd->argv, shell);
    }
}

void handle_sigchld(int signo) {
    (void)signo;
}

void prepare_pipe(cmd_t* cmd, shell_t* shell, int fd[2]) {
    pid_t input_sub = fork();
    if (input_sub == 0) {
        run_command(cmd->next, shell, fd);
        return;
    }
    pid_t output_sub = fork();
    if (output_sub == 0) {
        close(fd[1]);
        dup2(fd[0], 0);
        teach_child(get_full_path(cmd->argv[0], shell), cmd->argv, shell);
        return;
    }
    signal(SIGCHLD, handle_sigchld);
    int output = 0, input = 0;
    close(fd[0]);
    fcntl(fd[0], F_SETFL, O_NONBLOCK);
    while (waitpid(input_sub, &input, WNOHANG) == 0) {
        char buf[1024];
        int n = read(fd[0], buf, sizeof(buf));
        if (n > 0) {
            write(1, buf, n);
        }
    }
    close(fd[1]);
    close(fd[0]);
    waitpid(output_sub, &output, 0);
    if (input != 0)
        shell->state = handle_status(shell, cmd->next, input);
    if (output != 0)
        shell->state = handle_status(shell, cmd, output);
    // dprintf(2, "output: %d\n", WIFSIGNALED(output));
    // dprintf(2, "input: %d\n", WIFSIGNALED(input));
    // dprintf(2, "state: %d\n", shell->state);
    exit(shell->state);
    signal(SIGCHLD, SIG_DFL);
}

void execute(cmd_t* cmd, shell_t* shell)
{
    pid_t sub = fork();

    if (sub == 0) {
        shell->sub = getpid();
        run_command(cmd, shell, NULL);
        return;
    }
    waitpid(sub, &shell->state, 0);
    shell->state = handle_status(shell, cmd, shell->state);
    SHARED_STATUS = shell->state;
}
