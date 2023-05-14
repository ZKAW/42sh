/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** set
*/

#include "mysh.h"

void print_set(var_t *set)
{
    var_t *tmp;
    if (set->key == NULL) {
        return;
    }
    for (tmp = set; tmp->next != NULL; tmp = tmp->next) {
        if (strcmp(tmp->key, "TERM") == 0)
            printf("term\t%s\n", tmp->value);
        if ((strcmp(tmp->key, "?") != 0 && strcmp(tmp->key, "TERM") != 0))
            printf("%s\t%s\n", tmp->key, tmp->value);
    }
        if (strcmp(tmp->key, "TERM") == 0)
            printf("term\t%s\n", tmp->value);
        if ((strcmp(tmp->key, "?") != 0) && (strcmp(tmp->key, "TERM") != 0))
            printf("%s\t%s\n", tmp->key, tmp->value);
}

char* del_before(char *str)
{
    char *tmp = malloc(sizeof(char) * (strlen(str) + 1));
    int i = 0;
    int j = 0;
    for (; str[i] != '\0'; i++) {
        if (str[i] == '=')
            break;
    }
    i++;
    for (; str[i] != '\0'; i++) {
        tmp[j] = str[i];
        j++;
    }
    tmp[j] = '\0';
    return (tmp);
}

char* del_after(char *str)
{
    char *tmp = malloc(sizeof(char) * (strlen(str) + 1));
    int i = 0;
    int j = 0;
    for (; str[i] != '\0'; i++) {
        if (str[i] == '=')
            break;
        tmp[j] = str[i];
        j++;
    }
    tmp[j] = '\0';
    return (tmp);
}

char* delete_quotes(char *str)
{
    char *tmp = malloc(sizeof(char) * (strlen(str) + 1));
    int i = 0;
    int j = 0;
    for (; str[i] != '\0'; i++) {
        if (str[i] == '"')
            continue;
        tmp[j] = str[i];
        j++;
    }
    tmp[j] = '\0';
    return (tmp);
}

void builtin_set(BUILTIN_PARAMS)
{
    char *key = NULL; char *value = NULL; int argc = 0; int equal = 0;
    for (int i = 0; cmd->argv[i] != NULL; i++) argc++;
    char* tmp = array_to_str(cmd->argv);
    if (argc == 1) { print_set(shell->vars); return; }
    for (int i = 0; tmp[i] != '\0'; i++) {
        if (tmp[i] == '=') equal++;
    }
    if (argc == 2 && equal == 1) {
        key = strdup(del_after(cmd->argv[1]));
        value = strdup(del_before(cmd->argv[1]));
    }
    if (argc == 2 && equal == 0) {
        set_var(shell, cmd->argv[1], ""); return;
    }
    if ((argc == 3 || argc >= 4) && equal == 1) {
        key = strdup(del_after(cmd->argv[1]));
        value = strdup(del_before(delete_quotes(concatene_value(cmd->argv))));
    }
    if (equal == 1) set_var(shell, key, value);
}
