/*
** EPITECH PROJECT, 2022
** mini-shell1
** File description:
** cd.c
*/

#include "mysh.h"

char* find_envp(char* var, shell_t* shell)
{
    char** envp = shell->envp;
    int i = 0;
    for (i = 0; envp[i]; i++)
        if (!strncmp(envp[i], &var[1], strlen(&var[1])))
            return envp[i];
    return NULL;
}

void handle_cd_error(char* dir, shell_t* shell)
{
    char* error = strerror(errno);
    write(2, dir, strlen(dir));
    write(2, ": ", 2);
    write(2, error, strlen(error));
    write(2, ".\n", 2);
    shell->state = 1;
}

void builtin_cd(char** cmd, shell_t* shell)
{
    char actual_path[500], **var_env = shell->envp, *dir, *var;
    if (tablen(cmd) > 2) {
        throw_error("cd: Too many arguments.\n", shell, 1);
        return;
    }
    dir = (tablen(cmd) == 1 || !strcmp(cmd[1], "~")) ? "$HOME" : cmd[1];

    if (dir[0] == '$') {
        var = find_envp(dir, shell);
        var_env = tokenize_string(var, "=");
        dir = var_env[1];
    }
    if (!strcmp(dir, "-"))
        dir = shell->last_path;
    getcwd(actual_path, 500);
    if (chdir(dir) < 0) {
        handle_cd_error(dir, shell);
        return;
    }
    strcpy(shell->last_path, actual_path);
    update_cwd(shell);
}
