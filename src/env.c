/*
** EPITECH PROJECT, 2022
** mini-shell1
** File description:
** env.c
*/

#include <stdlib.h>
#include <unistd.h>
#include "../include/mini_shell.h"
#include "../include/my.h"

void print_env(char** cmd, shell_t* shell)
{
    print_array(shell->envp);
}

char** unset_var(char* var_name, char** envp)
{
    for (int i = 0; envp[i]; i++) {
        if (!my_strncmp(envp[i], var_name, my_strlen(var_name))) {
            envp = array_remove(i, envp);
            break;
        }
    }
    return envp;
}

void my_unsetenv(char** cmd, shell_t* shell)
{
    char **envp = shell->envp, *name_var;
    if (my_arraylen(cmd) < 2) {
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
