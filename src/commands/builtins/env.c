/*
** EPITECH PROJECT, 2022
** mini-shell1
** File description:
** env.c
*/

#include "mysh.h"

void builtin_env(char** cmd UNUSED, shell_t* shell)
{
    print_array(shell->envp);
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

char *get_env_var(char **env, char *key)
{
    char *value = NULL;

    for (int i = 0; env[i] != NULL; i++) {
        if (strncmp(env[i], key, strlen(key)) == 0) {
            value = strdup(env[i] + strlen(key));
            break;
        }
    }
    if (value != NULL && value[0] == '=') value++;
    if (value != NULL) value[strlen(value)] = '\0';

    return value;
}
