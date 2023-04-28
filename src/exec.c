/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** exec
*/

#include "mysh.h"

static void handle_child_error(char** argv)
{
    if (errno == 8) {
        write(2, argv[0], strlen(argv[0]));
        write(2, ": Exec format error. Wrong Architecture.\n", 41);
    }
    if (errno == 13) {
        write(2, argv[0], strlen(argv[0]));
        write(2, ": Permission denied.\n", 21);
    }
    exit(1);
}

void teach_child(char* path, char** cmd, shell_t* shell)
{
    int state = execve(path, cmd, shell->envp);
    if (state == -1) {
        handle_child_error(cmd);
    }
}

void run_command(cmd_t* cmd, shell_t* shell)
{
    int fd[2];
    char* path;
    if (!is_builtin(cmd->argv[0]) && !CHAR_IN_STR('/', cmd->argv[0])
    && !CHAR_IN_STR('\\', cmd->argv[0]))
        path = get_full_path(cmd->argv[0], shell);
    else
        path = cmd->argv[0];
    if (!path && !is_builtin(cmd->argv[0]) && not_existing(cmd->argv[0], shell))
        return;
    if (is_builtin(cmd->argv[0])) {
        run_builtin(cmd, shell);
        exit(shell->state);
    }   else {
        if (cmd->input_type != NONE)
            set_input(cmd, shell, fd);
        if (cmd->output_type != NONE)
            set_output(cmd);
        teach_child(path, cmd->argv, shell);
    }
}

void prepare_pipe(cmd_t* cmd, shell_t* shell, int fd[2])
{
    pid_t new_sub;
    new_sub = fork();
    if (new_sub == 0) {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        run_command(cmd->next, shell);
    } else {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
    }
}

void execute(cmd_t* cmd, shell_t* shell)
{
    pid_t sub;
    sub = fork();
    if (sub == 0) {
        shell->sub = getpid();
        run_command(cmd, shell);
    } else {
        waitpid(sub, &shell->state, 0);
        handle_error(shell);
    }
}
