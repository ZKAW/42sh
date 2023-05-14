/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** set
*/

#include "mysh.h"

int is_c_space(char c);
char *skip_whitespace(char *str);
void swap(var_t *a, var_t *b);
void bubble_sort(var_t *set);
int parse_var_line(char* tmp, char*** keys_ptr, char*** values_ptr);
char* ar_to_str(cmd_t* cmd);

void print_set(var_t *set)
{
    bubble_sort(set);
    var_t *tmp;
    if (set->key == NULL) return;
    for (tmp = set; tmp->next != NULL; tmp = tmp->next) {
        if (strcmp(tmp->key, "?") != 0)
            printf("%s\t%s\n", tmp->key, tmp->value);
    }
    if (strcmp(tmp->key, "?") != 0)
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

void builtin_set(BUILTIN_PARAMS)
{
<<<<<<< HEAD:src/commands/builtins/set/set.c
    if (error_handling_set(shell, cmd) == 1)
        return;
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
=======
    char buffer[5000];
    int argc = cmd->argc; char quote = '\0';
    char** keys = NULL, **value = NULL; int position = 0;
    if (argc == 1) {
        print_set(shell->vars);
        return;
>>>>>>> special_variables:src/commands/builtins/set.c
    }
    char* tmp = ar_to_str(cmd);
    int res = parse_var_line(tmp, &keys, &value);
    if (res == NAME) {
        return throw_error("set: Variable name must begin with a letter.\n",
            shell, 1);
    } else if (res == START) {
        return throw_error("set: Variable name must begin with a letter.\n",
            shell, 1);
    }
    for (int i = 0; keys[i] != NULL; i++) {
        set_var(shell, keys[i], value[i]);
    }
}
