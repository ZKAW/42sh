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

char* array_to_str(char **cmd)
{
    char *tmp = malloc(sizeof(char) * 500);
    int i = 0;
    int j = 0;
    for (; cmd[i] != NULL; i++) {
        for (int k = 0; cmd[i][k] != '\0'; k++) {
            tmp[j] = cmd[i][k];
            j++;
        }
        tmp[j] = ' ';
        j++;
    }
    tmp[j] = '\0';
    return (tmp);
}

char* delete_before_equal(char *str)
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

char* delete_after_equal(char *str)
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

void builtin_set(char** cmd, shell_t *shell)
{
    // SET KEY="VALUE" WITH VALUE HAVE MULTIPLE ARGS
    char *key = NULL; char *value = NULL;
    int argc = 0; int equal = 0;
    for (int i = 0; cmd[i] != NULL; i++) argc++;

    if (argc == 1) {
        print_set(shell->vars);
        return;
    }

    char* tmp = array_to_str(cmd);

    for (int i = 0; tmp[i] != '\0'; i++) {
        if (tmp[i] == '=')
            equal++;
    }

    if (argc == 4 && equal == 1) {
        if (strcmp(cmd[2], "=") == 0) {
            key = strdup(cmd[1]);
            value = strdup(cmd[3]);
        }
    }

    if (argc == 2 && equal == 1) {
        key = strdup(delete_after_equal(cmd[1]));
        value = strdup(delete_before_equal(cmd[1]));
    }

    if (argc == 2 && equal == 0) {
        set_var(shell, cmd[1], "");
        return;
    }

    set_var(shell, key, value);
}
