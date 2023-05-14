/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** special_vars
*/

#include "mysh.h"

void set_var(shell_t *shell, char *key, char *value)
{
    var_t *tmp;
    if (shell->vars->key == NULL) {
        shell->vars->key = key;
        shell->vars->value = value;
        shell->vars->next = NULL;
        return;
    }
    for (tmp = shell->vars; tmp->next != NULL; tmp = tmp->next) {
        if (strcmp(tmp->key, key) == 0) {
            tmp->value = value;
            return;
        }
    }
    if (strcmp(tmp->key, key) == 0) {
        tmp->value = value; return;
    }
    tmp->next = malloc(sizeof(var_t));
    tmp->next->key = key;
    tmp->next->value = value;
    tmp->next->next = NULL;
}

void unset_var(shell_t *shell, char *key)
{
    var_t *tmp = shell->vars;
    var_t *prev = NULL;
    if (tmp != NULL && strcmp(tmp->key, key) == 0) {
        shell->vars = tmp->next;
        free(tmp);
        return;
    }
    while (tmp != NULL && strcmp(tmp->key, key) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL) return;
    prev->next = tmp->next;
    free(tmp);
}

void init_special_vars(shell_t *shell)
{
    char *cwd = malloc(sizeof(char) * 500);
    cwd = getcwd(cwd, 500);
    set_var(shell, "term", get_env_var(shell->envp, "TERM"));
    set_var(shell, "cwd", cwd);
    set_var(shell, "?", "0");
    set_var(shell, "_", "");
}
