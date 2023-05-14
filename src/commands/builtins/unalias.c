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
    char* postcmd = get_postcmd_var(shell);
    if (postcmd == NULL)
        shell->postcmd = NULL;
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

void builtin_unalias(BUILTIN_PARAMS)
{
    alias_t *tmp; alias_t *tmp2;
    if (cmd->argv[1] == NULL)
        return throw_error("unalias: Too few arguments.\n", shell,
                        BUILTIN_ERROR);
    if (strcmp(cmd->argv[1], "*") == 0)
        return unalias_all(shell);
    for (tmp = shell->aliases; tmp->next != NULL; tmp = tmp->next) {
        if (strcmp(tmp->alias, cmd->argv[1]) == 0) {
            tmp2 = tmp->next; tmp->alias = tmp2->alias;
            tmp->command = tmp2->command;
            tmp->next = tmp2->next;
            free(tmp2); unalias_special_var(shell);
            return;
        }
    }
    if (tmp->alias == NULL) return;
    if (strcmp(tmp->alias, cmd->argv[1]) == 0) {
        shell->aliases = delete_last_element(shell->aliases);
        unalias_special_var(shell); return;
    }
}
