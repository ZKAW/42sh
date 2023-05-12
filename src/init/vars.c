/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** vars
*/

#include "mysh.h"

void init_vars(shell_t *shell)
{
    shell->precmd = NULL;
    shell->cwdcmd = NULL;
    shell->fignore = NULL;
    shell->vars = malloc(sizeof(var_t));
    shell->vars->key = NULL;
    shell->vars->value = NULL;
    shell->vars->next = NULL;
    init_special_vars(shell);
}
