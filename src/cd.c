/*
** EPITECH PROJECT, 2022
** mini-shell1
** File description:
** cd.c
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "../include/my.h"
#include "../include/mini_shell.h"

char* find_envp(char* var, shell_t* shell)
{
    char** envp = shell->envp;
    int i = 0;
    for (i = 0; envp[i]; i++)
        if (!my_strncmp(envp[i], &var[1], my_strlen(&var[1])))
            return envp[i];
    return NULL;
}

void throw_error(char* const strerror, shell_t* shell, int ernum)
{
    write(2, strerror, my_strlen(strerror));
    shell->state = ernum;
}

void change_directory(char** cmd, shell_t* shell)
{
    char actual_path[500], **var_env, **envp = shell->envp, *dir, *var;
    if (my_arraylen(cmd) > 2) {
        throw_error("cd: Too many arguments.\n", shell, 1);
        return;
    }
    dir = my_arraylen(cmd) == 2 ? cmd[1] : "$HOME";
    if (dir[0] == '$') {
        var = find_envp(dir, shell);
        var_env = string_split(var, '=');
        dir = var_env[1];
    }
    if (!my_strcmp(dir, "-"))
        dir = shell->last_path;
    getcwd(actual_path, 500);
    if (chdir(dir) < 0) {
        my_printf("%s: %s.\n", dir, strerror(errno));
        shell->state = 1;
        return;
    }
    my_strcpy(shell->last_path, actual_path);
}
