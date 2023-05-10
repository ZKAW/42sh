/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** exec
*/

#include "mysh.h"
#include <threads.h>

void sigchld_handler(int signo);

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

void wait_pipe_execution(pipe_t pipe, shell_t* shell)
{
    int output = 0, input = 0;
    close(pipe.fd[0]);
    fcntl(pipe.fd[0], F_SETFL, O_NONBLOCK);
    while (waitpid(pipe.input_pid, &input, WNOHANG) == 0) {
        char buf[1024];
        int n = read(pipe.fd[0], buf, sizeof(buf));
        if (n > 0) {
            write(1, buf, n);
        }
    }
    close(pipe.fd[1]);
    close(pipe.fd[0]);
    waitpid(pipe.output_pid, &output, 0);
    if (input != 0)
        shell->state = handle_status(input);
    if (output != 0)
        shell->state = handle_status(output);
    exit(shell->state);
}

void prepare_pipe(cmd_t* cmd, shell_t* shell, int fd[2])
{
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
    signal(SIGCHLD, sigchld_handler);
    wait_pipe_execution((pipe_t) {input_sub, output_sub, fd}, shell);
    signal(SIGCHLD, SIG_DFL);
}

void execute(cmd_t* cmd, shell_t* shell)
{
    pid_t sub = fork();
    if (cmd->is_background && cmd->job->pgid == -1) {
        cmd->job->pgid = sub;
        printf("[%d] %d\n", cmd->job->id, cmd->job->pgid);
        fflush(stdout);
    }

    if (sub == 0) {
        shell->sub = cmd->is_background ? setsid() : getpid();
        run_command(cmd, shell, NULL);
        return;
    }
    if (cmd->is_background)
        return;
    waitpid(sub, &shell->state, 0);
    shell->state = handle_status(shell->state);
    SHARED_STATUS = shell->state;
}
