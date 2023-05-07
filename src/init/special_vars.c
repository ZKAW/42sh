/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** special_vars
*/

#include "mysh.h"

void add_special_var(shell_t *shell, char *key, char *value)
{
    var_t *tmp = malloc(sizeof(var_t));
    if (shell->vars->key == NULL) {
        shell->vars->key = key;
        shell->vars->value = value;
        return;
    }
    for (tmp = shell->vars; tmp->next != NULL; tmp = tmp->next);
    tmp->next = malloc(sizeof(var_t));
    tmp->next->key = key;
    tmp->next->value = value;
    tmp->next->next = NULL;
}

void init_special_vars(shell_t *shell)
{
    add_special_var(shell, "cwd", NULL);
    add_special_var(shell, "cwdcmd", NULL);
    add_special_var(shell, "ignoreeof", NULL);
    add_special_var(shell, "term", "test");
    add_special_var(shell, "precmd", NULL);
    update_cwd(shell);
}