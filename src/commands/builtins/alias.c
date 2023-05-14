/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_alias
*/

#include "mysh.h"

char* concat_cmds_on_alias(char **buffer)
{
    int i = 3;
    char *tmp2 = malloc(sizeof(char) * (strlen(buffer[2]) + 1));
    tmp2[0] = '\0';
    tmp2 = strcat(tmp2, buffer[2]);
    for (; buffer[i] != NULL; i++) {
        tmp2 = realloc(tmp2, sizeof(char) * (strlen(tmp2) +
        strlen(buffer[i]) + 2));

        tmp2 = strcat(tmp2, " ");
        tmp2 = strcat(tmp2, buffer[i]);
    }
    tmp2 = strcat(tmp2, "\0");
    return (tmp2);
}

alias_t* add_alias(char **buffer, alias_t *alias)
{
    alias_t *tmp; char *tmp2 = concat_cmds_on_alias(buffer);
    if (alias->alias == NULL) {
        alias->alias = buffer[1]; alias->command = tmp2;
        alias->next = NULL; return (alias);
    }
    for (tmp = alias; tmp->next != NULL; tmp = tmp->next) {
        if (strcmp(tmp->alias, buffer[1]) == 0) {
            tmp->command = NULL;
            tmp->command = tmp2;
            return (alias);
        }
    }
    if (strcmp(tmp->alias, buffer[1]) == 0) {
        tmp->command = NULL;
        tmp->command = tmp2;
        return (alias);
    }
    tmp->next = malloc(sizeof(alias_t));
    tmp->next->alias = buffer[1]; tmp->next->command = tmp2;
    tmp->next->next = NULL; return (alias);
}

void show_alias(alias_t *alias, char **buffer)
{
    alias_t *tmp;
    if (alias->alias == NULL) {
        return;
    }
    for (tmp = alias; tmp != NULL; tmp = tmp->next) {
        if (strcmp(tmp->alias, buffer[1]) == 0) {
            printf("%s\n", tmp->command);
            return;
        }
    }
    if (strcmp(tmp->alias, buffer[1]) == 0) {
        printf("%s\n", tmp->command);
        return;
    }
}

void print_alias(alias_t *alias)
{
    alias_t *tmp;
    if (alias->alias == NULL) {
        return;
    }
    for (tmp = alias; tmp->next != NULL; tmp = tmp->next) {
        if (have_space(tmp->command) == 1)
            printf("%s\t(%s)\n", tmp->alias, tmp->command);
        else
            printf("%s\t%s\n", tmp->alias, tmp->command);
    }
    if (have_space(tmp->command) == 1)
        printf("%s\t(%s)\n", tmp->alias, tmp->command);
    else
        printf("%s\t%s\n", tmp->alias, tmp->command);
}

void builtin_alias(BUILTIN_PARAMS)
{
    int argc = 0;
    for (int i = 0; cmd->argv[i] != NULL; i++)
        argc++;

    set_status(shell, 0);
    if (argc == 1) {
        print_alias(shell->aliases);
        return;
    }

    if (argc == 2) {
        show_alias(shell->aliases, cmd->argv);
        return;
    }
    add_alias(cmd->argv, shell->aliases);
    alias_special_var(shell);
}
