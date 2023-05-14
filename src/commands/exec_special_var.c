/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** exec_special_var
*/

#include "mysh.h"

//same but global because have repetitif code

void alias_special_var(shell_t *shell)
{
    char *precmd = get_precmd_var(shell);
    if (precmd != NULL)
        shell->precmd = precmd;
    char* cwdcmd = get_cwdcmd_var(shell);
    if (cwdcmd != NULL)
        shell->cwdcmd = cwdcmd;
    char* fignore = get_fignore_var(shell);
    if (fignore != NULL)
        shell->fignore = fignore;
    char* postcmd = get_postcmd_var(shell);
    if (postcmd != NULL)
        shell->postcmd = postcmd;
}

char* get_fignore_var(shell_t* shell)
{
    char *alias = NULL; alias_t *tmp = NULL;
    if (shell->aliases->alias == NULL)
        return NULL;
    for (tmp = shell->aliases; tmp->next != NULL; tmp = tmp->next) {
        if (strcmp(tmp->alias, "fignore") == 0)
            alias = strdup(tmp->command);
    }
    if (strcmp(tmp->alias, "fignore") == 0)
        alias = strdup(tmp->command);

    return alias;
}

char* get_cwdcmd_var(shell_t* shell)
{
    char *alias = NULL; alias_t *tmp = NULL;
    if (shell->aliases->alias == NULL)
        return NULL;
    for (tmp = shell->aliases; tmp->next != NULL; tmp = tmp->next) {
        if (strcmp(tmp->alias, "cwdcmd") == 0)
            alias = strdup(tmp->command);
    }
    if (strcmp(tmp->alias, "cwdcmd") == 0)
        alias = strdup(tmp->command);

    return alias;
}

char* get_precmd_var(shell_t* shell)
{
    char *alias = NULL; alias_t *tmp = NULL;
    if (shell->aliases->alias == NULL)
        return NULL;
    for (tmp = shell->aliases; tmp->next != NULL; tmp = tmp->next) {
        if (strcmp(tmp->alias, "precmd") == 0)
            alias = strdup(tmp->command);
    }
    if (strcmp(tmp->alias, "precmd") == 0)
        alias = strdup(tmp->command);

    return alias;
}

char *get_local_var(shell_t *shell, char *key)
{
    var_t *tmp;
    if (shell->vars == NULL)
        return NULL;

    for (tmp = shell->vars; tmp->next != NULL; tmp = tmp->next) {
        if (my_strcmp(tmp->key, key) == 0)
            return tmp->value;
    }
    if (my_strcmp(tmp->key, key) == 0)
        return tmp->value;
    return NULL;
}
