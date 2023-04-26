/*
** EPITECH PROJECT, 2022
** mini-shell2
** File description:
** builtin.c
*/

#include "../include/my.h"
#include "../include/mini_shell.h"

void print_env(char** cmd, shell_t* shell);
void show_history(char** cmd, shell_t* shell);

int is_builtin(char* path)
{
    char* cmd_names[6] = {"cd", "env", "setenv", "unsetenv", "history",NULL};
    for (int i = 0; i < 5; i++) {
        if (!my_strcmp(path, cmd_names[i]))
            return 1;
    }
    return 0;
}

void run_builtin(cmd_t* cmd, shell_t* shell)
{
    int i;
    char** argv = cmd->argv;
    char* cmd_names[6] = {"cd", "env", "setenv", "unsetenv", "history", NULL};
    void (*cmd_funcs[6]) (char** cmd, shell_t* shell) = {
        change_directory, print_env, my_setenv, my_unsetenv, show_history
    };
    for (i = 0; i < 4 && my_strcmp(cmd_names[i], argv[0]); i++);
    (cmd_funcs[i])(argv, shell);
}
