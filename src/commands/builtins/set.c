/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** set
*/

#include "mysh.h"

int is_c_space(char c);

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

//va discord le sang

// void set()
// {
//     if (argc == 2 && equal == 1) {
//         key = strdup(del_after(cmd->argv[1]));
//         value = strdup(del_before(cmd->argv[1]));
//     }
//     if ((argc == 3 || argc >= 4) && equal == 1) {
//         key = strdup(del_after(cmd->argv[1]));
//         value = strdup(del_before(delete_quotes(concatene_value(cmd->argv))));
//     }
//     if (equal == 1) set_var(shell, key, value);
// }

// void builtin_set(BUILTIN_PARAMS)
// {
//     char *key = NULL; char *value = NULL; int argc = cmd->argc; int equal = 0;
//     char* tmp = array_to_str(cmd->argv);
//     if (argc == 1) { print_set(shell->vars); return; }
//     for (int i = 0; tmp[i] != '\0'; i++) {
//         if (tmp[i] == '=') equal++;
//     }
//     if (argc == 2 && equal == 0) {
//         set_var(shell, cmd->argv[1], ""); return;
//     }

//     while (equal > 1)
//         equal--;

// }

char* ar_to_str(cmd_t* cmd)
{
    char str[4096] = {0};
    char** argv = cmd->argv;
    int* type = cmd->arg_type;
    for (int i = 1; argv[i] != NULL; i++) {
        if (type[i] == QUOTTED) my_strcat(str, "\'");
        my_strcat(str, argv[i]);
        if (type[i] == QUOTTED) my_strcat(str, "\'");
        my_strcat(str, " ");
    }
    return strdup(str);
}

char *skip_whitespace(char *str);

void builtin_set(BUILTIN_PARAMS)
{
    char buffer[5000];
    int argc = cmd->argc; int equal = 0, has_error = 0, ws_before = 0, ws_error = 0;
    char quote = '\0';
    char** keys = NULL, **value = NULL;
    int position = 0;
    if (argc == 1) { print_set(shell->vars); return; }
    char* tmp = ar_to_str(cmd);
    while (*tmp != '\0' && *tmp) {
        buffer[0] = '\0';
        if (*tmp == '=') {
            equal++;
            tmp++;
            if (is_c_space)
            continue;
        }
        if (*tmp == '\0') break;
        if ((ws_before && is_c_space(*tmp) == 0)
        || (!ws_before && is_c_space(*tmp) == 1)) {
            ws_error = 1;
            break;
        }
        if (*tmp == '\'' || *tmp == '"') {
            quote = *tmp;
            tmp++;
            while (*tmp != quote && *tmp != '\0') {
                strncat(buffer, tmp, 1);
                tmp++;
            }
            tmp++;
        } else {
            tmp = copy_until(buffer, tmp, " \t\n=");
        }
        if (equal == 0) {
            if (keys && keys[position] != NULL) {
                has_error = 1;
                break;
            }
            keys = realloc(keys, sizeof(char*) * (position + 2));
            keys[position] = strdup(buffer);
            keys[position + 1] = NULL;
            if (is_c_space(*tmp)) ws_before = 1;
        } else {
            value = realloc(value, sizeof(char*) * (position + 2));
            value[position++] = strdup(buffer);
            equal--;
            ws_before = 0;
            tmp = skip_whitespace(tmp);
        }
    }
    if (keys) keys[position] = NULL;
    if (value) value[position] = NULL;
    if (has_error) {
        dprintf(2, "set: Variable name must contain alphanumeric characters.\n");
        //return;
    }
    if (ws_error) {
        dprintf(2, "set: Variable name must begin with a letter.\n");
        //return;
    }
    for (int i = 0; keys[i] != NULL; i++) {
        dprintf(1, "key: |%s| - value: |%s| \n", keys[i], value[i]);
    }
    //set_var(shell, key, value);
}
