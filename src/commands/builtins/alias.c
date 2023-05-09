/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_alias
*/

#include "mysh.h"

alias_t* add_alias(char **buffer, alias_t *alias)
{
    int i = 3; char *tmp2 = malloc(sizeof(char) * 100);
    alias_t *tmp;
    tmp2 = strcat(tmp2, buffer[2]);
    for (; buffer[i] != NULL; i++) {
        tmp2 = strcat(tmp2, " ");
        tmp2 = strcat(tmp2, buffer[i]);
    }
    tmp2 = strcat(tmp2, "\0");

    if (alias->alias == NULL) {
        alias->alias = buffer[1];
        alias->command = tmp2;
        alias->next = NULL;
        return (alias);
    }
    for (tmp = alias; tmp->next != NULL; tmp = tmp->next) {
        if (my_strcmp(tmp->alias, buffer[1]) == 0) {
            tmp->command = NULL;
            tmp->command = tmp2;
            return (alias);
        }
    }
    if (my_strcmp(tmp->alias, buffer[1]) == 0) {
        tmp->command = NULL;
        tmp->command = tmp2;
        return (alias);
    }
    tmp->next = malloc(sizeof(alias_t));
    tmp->next->alias = buffer[1];
    tmp->next->command = tmp2;
    tmp->next->next = NULL;
    return (alias);
}

void show_alias(alias_t *alias, char **buffer)
{
    alias_t *tmp;
    if (alias->alias == NULL) {
        my_putstr("No alias\n", 1);
        return;
    }
    for (tmp = alias; tmp != NULL; tmp = tmp->next) {
        if (my_strcmp(tmp->alias, buffer[1]) == 0) {
            my_putstr(tmp->command, 1);
            my_putstr("\n", 1);
            return;
        }
    }
    if (my_strcmp(tmp->alias, buffer[1]) == 0) {
        my_putstr(tmp->command, 1);
        my_putstr("\n", 1);
        return;
    }
    my_putstr("Alias not found\n", 1);
}

void print_alias(alias_t *alias)
{
    alias_t *tmp;
    if (alias->alias == NULL) {
        my_putstr("No alias\n", 1);
        return;
    }
    for (tmp = alias; tmp->next != NULL; tmp = tmp->next) {
        printf("%s\t(%s)\n", tmp->alias, tmp->command);
    }
    printf("%s\t(%s)\n", tmp->alias, tmp->command);
}

void builtin_alias(char** cmd, shell_t *shell)
{
    int argc = 0;
    for (int i = 0; cmd[i] != NULL; i++)
        argc++;

    if (argc == 1) {
        print_alias(shell->aliases);
        return;
    }

    if (argc == 2) {
        show_alias(shell->aliases, cmd);
        return;
    }
    add_alias(cmd, shell->aliases);
}
