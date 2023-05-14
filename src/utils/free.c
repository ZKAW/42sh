/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** free
*/

#include "mysh.h"

void safe_free(void *ptr)
{
    if (ptr)
        free(ptr);
}

void free_arr(char** arr)
{
    for (int i = 0; arr[i] != NULL; i++) {
        if (arr[i])
            safe_free(arr[i]);
    }
    if (arr)
        safe_free(arr);
}
