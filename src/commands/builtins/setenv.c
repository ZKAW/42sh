/*
** EPITECH PROJECT, 2022
** mini-shell2
** File description:
** setenv.c
*/

#include <stddef.h>
#include "mysh.h"

int check_setenv_err(char *key, int len)
{
    if (is_str_alphanum(key) == 0) {
        fputs("setenv: Variable name must contain ", stderr);
        fputs("alphanumeric characters.\n", stderr);
        return (1);
    }
    if (len > 3) {
        fputs("setenv: Too many arguments.\n", stderr);
        return (1);
    }
    return (0);
}

static void setenv_helper(shell_t *shell, char *key, char *value)
{
    char *new_env = malloc(sizeof(char) * (strlen(key) + strlen(value) + 2));
    strcpy(new_env, key);
    strcat(new_env, "=");
    strcat(new_env, value);
    int i = 0;
    for (; shell->envp[i] != NULL; i++) {
        if (strncmp(shell->envp[i], key, strlen(key)) == 0
            && shell->envp[i][strlen(key)] == '=') {
            shell->envp[i] = strdup(new_env);
            return;
        }
    }
    shell->envp = array_append(shell->envp, new_env);
}

void builtin_setenv(BUILTIN_PARAMS)
{
    int len = tablen(cmd->argv);
    if (len <= 1) {
        builtin_env(cmd, shell);
        return;
    }
    char *key = cmd->argv[1];
    char *value = cmd->argv[2];

    if (tablen(cmd->argv) == 2) {
        value = malloc(sizeof(char) * 1);
        value[0] = '\0';
    }
    if (check_setenv_err(key, len)) {
        shell->state = BUILTIN_ERROR;
        set_status(shell, BUILTIN_ERROR);
        return;
    }
    setenv_helper(shell, key, value);
}
