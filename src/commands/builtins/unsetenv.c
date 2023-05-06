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

void builtin_unsetenv(char** cmd, shell_t* shell)
{
    char **envp = shell->envp;
    if (tablen(cmd) < 2) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        shell->state = 1;
        return;
    }
    for (int i = 1; cmd[i]; i++) {
        envp = unset_var(cmd[i], envp);
    }
    shell->state = 0;
    shell->envp = envp;
}
