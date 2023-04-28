/*
** EPITECH PROJECT, 2022
** mini-shell1
** File description:
** env.c
*/

#include "mysh.h"

char** get_env_paths(char** envp)
{
    int i;
    char** paths;
    for (i = 0; strncmp(envp[i], "PATH", 4); i++);
    paths = tokenize_string(&envp[i][5], ":");
    for (i = 0; paths[i] != NULL; i++)
        paths[i] = str_append(paths[i], "/");
    return paths;
}

char** envp_cpy(char** envp)
{
    int i;
    char** copy = malloc(sizeof(char*) * (tablen(envp) + 1));
    for (i = 0; envp[i]; i++)
        copy[i] = strdup(envp[i]);
    copy[i] = NULL;
    return copy;
}

void builtin_env(char** cmd UNUSED, shell_t* shell)
{
    print_array(shell->envp);
}
