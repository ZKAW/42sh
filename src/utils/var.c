/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** var
*/

#include "mysh.h"

void swap(var_t *a, var_t *b);

void bubble_sort(var_t *set)
{
    int swapped;
    var_t *ptr1;
    var_t *lptr = NULL;
    if (set == NULL)
        return;
    do {
        swapped = 0;
        ptr1 = set;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->key, ptr1->next->key) > 0) {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void swap(var_t *a, var_t *b)
{
    char *tmp_key = a->key;
    char *tmp_value = a->value;
    a->key = b->key;
    a->value = b->value;
    b->key = tmp_key;
    b->value = tmp_value;
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

char* concatene_value(char **cmd)
{
    int len = 0;
    for (int i = 0; cmd[i] != NULL; i++) {
        len += strlen(cmd[i]);
    }
    char *tmp = malloc(sizeof(char) * (len + 1));
    int j = 0;
    for (int i = 0; cmd[i] != NULL; i++) {
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
