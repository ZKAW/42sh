/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** unsetenv
*/

#include "mysh.h"

static char** unset_env(char* var_name, char** envp)
{
    for (int i = 0; envp[i]; i++) {
        if (!strncmp(envp[i], var_name, strlen(var_name))) {
            envp = array_remove(i, envp);
            break;
        }
    }
    return envp;
}

void builtin_unsetenv(BUILTIN_PARAMS)
{
    char **envp = shell->envp;
    if (tablen(cmd->argv) < 2) {
        throw_error("unsetenv: Too few arguments.\n", shell, BUILTIN_ERROR);
        return;
    }
    for (int i = 1; cmd->argv[i]; i++) {
        envp = unset_env(cmd->argv[i], envp);
    }
    shell->state = 0;
    shell->envp = envp;
}
