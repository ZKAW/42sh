/*
** EPITECH PROJECT, 2022
** mini-shell2
** File description:
** cmd_tools.c
*/

#include <sys/stat.h>
#include <stdlib.h>
#include "../include/my.h"
#include "../include/mini_shell.h"

char* clean_str(char* line)
{
    char* tmp = malloc(sizeof(char) * (my_strlen(line) + 1));
    if (line[my_strlen(line) - 1] == '\n')
        my_strncpy(tmp, line, my_strlen(line) - 1);
    else
        my_strcpy(tmp, line);
    return tmp;
}

char* get_full_path(char* input, shell_t* shell)
{
    struct stat info;
    char** paths = get_env_paths(shell->envp);
    char* test_path;
    int input_s = my_strlen(input);
    for (int i = 0; paths[i]; i++) {
        test_path = malloc(sizeof(char) * (my_strlen(paths[i]) + input_s + 1));
        my_strcpy(test_path, paths[i]);
        my_strcat(test_path, input);
        if (stat(test_path, &info) != -1)
            return test_path;
        free(test_path);
    }
    return NULL;
}

list_t* reverse_cmd(list_t* head)
{
    list_t *current = head, *prev = NULL, *next = NULL, *new_head = NULL;
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
