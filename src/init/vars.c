/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** vars
*/

#include "mysh.h"

char* get_postcmd_var(shell_t* shell)
{
    char *alias = NULL; alias_t *tmp = NULL;
    if (shell->aliases->alias == NULL)
        return NULL;
    for (tmp = shell->aliases; tmp->next != NULL; tmp = tmp->next) {
        if (strcmp(tmp->alias, "postcmd") == 0)
            alias = strdup(tmp->command);
    }
    if (strcmp(tmp->alias, "postcmd") == 0)
        alias = strdup(tmp->command);

    return alias;
}

void init_vars(shell_t *shell)
{
    shell->precmd = NULL;
    shell->postcmd = NULL;
    shell->cwdcmd = NULL;
    shell->fignore = NULL;
    shell->vars = malloc(sizeof(var_t));
    shell->vars->key = NULL;
    shell->vars->value = NULL;
    shell->vars->next = NULL;
    init_special_vars(shell);
}
