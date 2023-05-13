/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** unset
*/

#include "mysh.h"

var_t *unset_last_elem(var_t *unset)
{
    var_t *tmp;
    var_t *tmp2;
    if (unset->next == NULL) {
        unset->key = NULL;
        unset->value = NULL;
        return (unset);
    }
    for (tmp = unset; tmp->next != NULL; tmp = tmp->next) {
        tmp2 = tmp;
    }
    tmp2->next = NULL;
    free(tmp);
    return (unset);
}

void builtin_unset(char** cmd, shell_t *shell)
{
    var_t *tmp; var_t *tmp2;
    if (cmd[1] == NULL)
        return throw_error("var: Too few arguments.\n", shell, 1);

    if (strcmp(cmd[1], "term") == 0)
        cmd[1] = "TERM";

    for (tmp = shell->vars; tmp->next != NULL; tmp = tmp->next) {
        if (strcmp(tmp->key, cmd[1]) == 0) {
            tmp2 = tmp->next;
            tmp->key = tmp2->key;
            tmp->value = tmp2->value;
            tmp->next = tmp2->next;
            free(tmp2);
            return;
        }
    } if (strcmp(tmp->key, cmd[1]) == 0) {
        shell->vars = unset_last_elem(shell->vars);
        return;
    }
}
