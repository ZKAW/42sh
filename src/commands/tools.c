/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** tools
*/

#include "mysh.h"

char* get_full_path(char* cmd, shell_t* shell)
{
    char *PATH = get_env_var(shell->envp, "PATH");
    if (PATH == NULL) return cmd;
    char **path_dirs = tokenize_string(PATH, ":");
    char *abs_path = NULL;

    for (int i = 0; path_dirs[i] != NULL; i++) {
        if (path_dirs[i][strlen(path_dirs[i]) - 1] == '\n') {
            path_dirs[i][strlen(path_dirs[i]) - 1] = '\0';
        }
        abs_path = concat_path(path_dirs[i], cmd);
        if (access(abs_path, F_OK) != -1) {
            return (abs_path);
        }
        free(abs_path);
    }
    return cmd;
}

list_t* reverse_cmd(list_t* head)
{
    list_t *current = head, *prev = NULL, *next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
    return head;
}

void reverse_head(cmd_t** head)
{
    cmd_t* current = *head;
    cmd_t* temp = NULL;

    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if (temp != NULL) {
        *head = temp->prev;
    }
}
