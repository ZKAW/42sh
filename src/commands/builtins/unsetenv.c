/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** unsetenv
*/

#include "mysh.h"

static char** unset_var(char* var_name, char** envp)
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
    char **cmd = command->argv;
    if (tablen(cmd) < 2) {
        throw_error("unsetenv: Too few arguments.\n", shell, 1);
        return;
    }
    for (int i = 1; cmd[i]; i++) {
        envp = unset_var(cmd[i], envp);
    }
    shell->state = 0;
    shell->envp = envp;
}
