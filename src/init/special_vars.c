/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** special_vars
*/

#include "mysh.h"

void set_var(shell_t *shell, char *key, char *value)
{
    for (var_t *tmp = shell->vars; tmp->next != NULL; tmp = tmp->next) {
        if (my_strcmp(tmp->key, key) == 0) {
            tmp->value = value;
            return;
        }
    }
    var_t *tmp2 = malloc(sizeof(var_t));
    if (shell->vars->key == NULL) {
        shell->vars->key = key;
        shell->vars->value = value;
        return;
    }
    for (tmp2 = shell->vars; tmp2->next != NULL; tmp2 = tmp2->next);
    tmp2->next = malloc(sizeof(var_t));
    tmp2->next->key = key;
    tmp2->next->value = value;
    tmp2->next->next = NULL;
}

void init_special_vars(shell_t *shell)
{
    char *cwd = malloc(sizeof(char) * 500);
    cwd = getcwd(cwd, 500);
    set_var(shell, "cwd", cwd);
    set_var(shell, "term", get_env_var(shell->envp, "TERM"));
}
