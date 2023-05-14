/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** exec_alias
*/

#include "mysh.h"

char *get_alias(shell_t *shell, char *key)
{
    alias_t *tmp = shell->aliases;
    if (tmp->alias == NULL) return NULL;
    if (my_strcmp(key, "$") == 0) return NULL;
    for (int i = 0; tmp->next != NULL; i++) {
        if (my_strcmp(tmp->alias, key) == 0)
            return tmp->command;
        tmp = tmp->next;
    }
    if (my_strcmp(tmp->alias, key) == 0)
        return tmp->command;
    return NULL;
}

void replace_str_to_array(char** array, char* str, int index, cmd_t* cmd)
{
    char** new_array = malloc(sizeof(char*) * (tablen(array) + 1));
    int i = 0;
    for (; i < index; i++)
        new_array[i] = array[i];
    char** splitted = malloc(sizeof(char*) * (tablen(array) + 1));
    splitted = my_str_to_word_array(str, ' ');
    for (int j = 0; splitted[j] != NULL; j++) {
        new_array[i] = splitted[j];
        i++;
    }
    for (; array[i + 1] != NULL; i++)
        new_array[i + 1] = array[i + 1];
    new_array[i + 1] = NULL;
    for (int j = 0; splitted[j] != NULL; j++)
        cmd->argv[j] = splitted[j];
}

int cmd_is_alias(cmd_t* cmd, shell_t* shell)
{
    if (cmd->argv == NULL) return 0;
    for (int i = 0; cmd->argv[i] != NULL; i++) {
        char *alias = get_alias(shell, cmd->argv[i]);
        if (alias != NULL) {
            replace_arr_at_index(&cmd->argv, tokenize_string(alias, " "), i);
            return 1;
        }
    }
    return 0;
}
