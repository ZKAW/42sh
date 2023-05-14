/*
** EPITECH PROJECT, 2022
** mini-shell2
** File description:
** builtin.c
*/

#include "mysh.h"

int is_builtin(char* path)
{
    if (!path)
        return 0;
    for (int i = 0; builtin_cmds[i].name; i++) {
        if (strcmp(builtin_cmds[i].name, path) == 0)
            return 1;
    }
    return 0;
}

void restore_stdin_stdout(int saved_input, int saved_output)
{
    dup2(saved_input, 0);
    dup2(saved_output, 1);
    close(saved_input);
    close(saved_output);
}

void run_builtin(cmd_t* cmd, shell_t* shell)
{
    int fd[2];
    int saved_input = dup(0), saved_output = dup(1);
    int new_input = 0, new_output = 0;
    if (getpid() == shell->pid) {
        if (cmd->output_type != NONE)
            new_output = set_output(cmd, fd);
        if (cmd->input_type != NONE)
            new_input = set_input(cmd, shell, fd);
    }
    for (int i = 0; builtin_cmds[i].name; i++) {
        if (strcmp(builtin_cmds[i].name, cmd->path) == 0) {
            builtin_cmds[i].func(cmd, shell);
            break;
        }
    }
    fflush(stdout);
    if (new_input) close(new_input);
    if (new_output) close(new_output);
    restore_stdin_stdout(saved_input, saved_output);
}
