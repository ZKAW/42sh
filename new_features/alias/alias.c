/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin_alias
*/

#include "../../include/mini_shell.h"
#include "../../include/my.h"

alias_t* add_alias(char **buffer, alias_t *alias)
{
    int i = 3;
    for (; buffer[i] != NULL; i++) {
        buffer[2] = strcat(buffer[2], " ");
        buffer[2] = strcat(buffer[2], buffer[i]);
    }
    alias_t *tmp;
    if (alias->alias == NULL) {
        alias->alias = buffer[1];
        alias->command = buffer[2];
        alias->next = NULL;
        return (alias);
    }
    for (tmp = alias; tmp->next != NULL; tmp = tmp->next) {
        if (my_strcmp(tmp->alias, buffer[1]) == 0) {
            tmp->command = NULL;
            tmp->command = buffer[2];
            return (alias);
        }
    }
    if (my_strcmp(tmp->alias, buffer[1]) == 0) {
        tmp->command = NULL;
        tmp->command = buffer[2];
        return (alias);
    }
    tmp->next = malloc(sizeof(alias_t));
    tmp->next->alias = buffer[1];
    tmp->next->command = buffer[2];
    tmp->next->next = NULL;
    return (alias);
}

void show_alias(alias_t *alias, char **buffer)
{
    alias_t *tmp;
    if (alias->alias == NULL) {
        my_putstr("No alias\n");
        return;
    }
    for (tmp = alias; tmp != NULL; tmp = tmp->next) {
        if (my_strcmp(tmp->alias, buffer[1]) == 0) {
            my_putstr(tmp->command);
            my_putstr("\n");
            return;
        }
    }
    if (my_strcmp(tmp->alias, buffer[1]) == 0) {
        my_putstr(tmp->command);
        my_putstr("\n");
        return;
    }
    my_putstr("Alias not found\n");
}

void modify_alias(alias_t *alias, char **buffer)
{
    alias_t *tmp;
    for (tmp = alias; tmp != NULL; tmp = tmp->next) {
        if (my_strcmp(tmp->alias, buffer[1]) == 0) {
            tmp->command = buffer[2];
            return;
        }
    }
    my_putstr("Alias not found\n");
}

void print_alias(alias_t *alias, char **buffer)
{
    alias_t *tmp;
    if (alias->alias == NULL) {
        my_putstr("No alias\n");
        return;
    }
    for (tmp = alias; tmp->next != NULL; tmp = tmp->next) {
        printf("%s\t(%s)\n", tmp->alias, tmp->command);
    }
    printf("%s\t(%s)\n", tmp->alias, tmp->command);
}

alias_t* init_alias(char* argv, shell_t *shell)
{
    char **buffer = tokenize_string(argv, " \n");
    int argc = 0;
    for (int i = 0; buffer[i] != NULL; i++)
        argc++;

    if (argc == 1) {
        print_alias(shell->alias, buffer);
        return (shell->alias);
    }

    if (argc == 2) {
        show_alias(shell->alias, buffer);
        return (shell->alias);
    }
    return (add_alias(buffer, shell->alias));
}
