/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** unalias
*/

#include "mysh.h"

alias_t *delete_last_element(alias_t *alias)
{
    alias_t *tmp;
    alias_t *tmp2;
    if (alias->next == NULL) {
        alias->alias = NULL;
        alias->command = NULL;
        return (alias);
    }
    for (tmp = alias; tmp->next != NULL; tmp = tmp->next) {
        tmp2 = tmp;
    }
    tmp2->next = NULL;
    free(tmp);
    return (alias);
}

void unalias_special_var(shell_t *shell)
{
    char *precmd = get_precmd_var(shell);
    if (precmd == NULL)
        shell->precmd = NULL;
    char* cwdcmd = get_cwdcmd_var(shell);
    if (cwdcmd == NULL)
        shell->cwdcmd = NULL;
    char* fignore = get_fignore_var(shell);
    if (fignore == NULL)
        shell->fignore = NULL;
}

void unalias_all(shell_t *shell)
{
    alias_t *tmp; alias_t* tmp2;
    for (tmp = shell->aliases; tmp != NULL; tmp = tmp2) {
        tmp2 = tmp->next;
        free(tmp);
    }
    shell->aliases = malloc(sizeof(alias_t));
    shell->aliases->alias = NULL;
    shell->aliases->command = NULL;
    shell->aliases->next = NULL;
    unalias_special_var(shell);
}

void builtin_unalias(char** cmd, shell_t *shell)
{
    alias_t *tmp; alias_t *tmp2;
    if (cmd[1] == NULL) {
        my_putstr("unalias: Too few arguments.\n", 1); return;
    }
    for (tmp = shell->aliases; tmp->next != NULL; tmp = tmp->next) {
        if (my_strcmp(tmp->alias, cmd[1]) == 0) {
            tmp2 = tmp->next;
            tmp->alias = tmp2->alias;
            tmp->command = tmp2->command;
            tmp->next = tmp2->next;
            free(tmp2);
            unalias_special_var(shell);
            return;
        }
    }
    if (my_strcmp(tmp->alias, cmd[1]) == 0) {
        shell->aliases = delete_last_element(shell->aliases);
        unalias_special_var(shell); return;
    }
    my_putstr("unalias: No such alias.\n", 1);
}
