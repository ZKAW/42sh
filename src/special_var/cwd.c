/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** cwd
*/

#include "mysh.h"

void update_cwd(shell_t *shell)
{
    char *cwd = malloc(sizeof(char) * 500);
    cwd = getcwd(cwd, 500);
    for (var_t *tmp = shell->vars; tmp != NULL; tmp = tmp->next) {
        if (my_strcmp(tmp->key, "cwd") == 0)
            tmp->value = cwd;
    }
}