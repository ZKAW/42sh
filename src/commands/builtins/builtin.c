/*
** EPITECH PROJECT, 2022
** mini-shell2
** File description:
** builtin.c
*/

#include "mysh.h"

int is_builtin(char* path)
{
    for (int i = 0; builtin_cmds[i].name; i++) {
        if (strcmp(builtin_cmds[i].name, path) == 0)
            return 1;
    }
    return 0;
}

void run_builtin(cmd_t* cmd, shell_t* shell)
{
    for (int i = 0; builtin_cmds[i].name; i++) {
        if (strcmp(builtin_cmds[i].name, cmd->path) == 0) {
            builtin_cmds[i].func(cmd->argv, shell);
            return;
        }
    }
}
