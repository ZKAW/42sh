/*
** EPITECH PROJECT, 2022
** mini-shell2
** File description:
** builtin.c
*/

#include "mysh.h"

int is_builtin(char* path)
{
    char* cmd_names[6] = {"cd", "env", "setenv", "unsetenv", "exit", NULL};
    for (int i = 0; i < 4; i++) {
        if (!strcmp(path, cmd_names[i]))
            return 1;
    }
    return 0;
}

void run_builtin(cmd_t* cmd, shell_t* shell)
{
    int i;
    char** argv = cmd->argv;
    char* cmd_names[6] = {"cd", "env", "setenv", "unsetenv", "exit", NULL};
    void (*cmd_funcs[6]) (char** cmd, shell_t* shell) = {
        builtin_cd, builtin_env, builtin_setenv, builtin_unsetenv, builtin_exit
    };
    for (i = 0; i < 4 && strcmp(cmd_names[i], argv[0]); i++);
    (cmd_funcs[i])(argv, shell);
}
