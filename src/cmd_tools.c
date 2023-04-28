/*
** EPITECH PROJECT, 2022
** mini-shell2
** File description:
** cmd_tools.c
*/

#include "mysh.h"

char* get_full_path(char* input, shell_t* shell)
{
    struct stat info;
    char** paths = get_env_paths(shell->envp);
    char* test_path;
    int input_s = strlen(input);
    for (int i = 0; paths[i]; i++) {
        test_path = malloc(sizeof(char) * (strlen(paths[i]) + input_s + 1));
        strcpy(test_path, paths[i]);
        strcat(test_path, input);
        if (stat(test_path, &info) != -1)
            return test_path;
        free(test_path);
    }
    return NULL;
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
