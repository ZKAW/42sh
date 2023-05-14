/*
** EPITECH PROJECT, 2022
** mini-shell1
** File description:
** env.c
*/

#include "mysh.h"

void builtin_env(BUILTIN_PARAMS)
{
    (void)cmd;
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
