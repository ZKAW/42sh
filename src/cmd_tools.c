/*
** EPITECH PROJECT, 2022
** mini-shell2
** File description:
** cmd_tools.c
*/

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
