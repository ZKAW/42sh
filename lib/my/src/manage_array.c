/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** manage_array
*/

#include <stdlib.h>
#include <string.h>
#include "lib.h"

char** array_append(char** array, char* const str)
{
    int old_lenght = tablen(array);
    char** new_arr = malloc(sizeof(char*) * (old_lenght + 2));
    for (int i = 0; array[i] != NULL; i++)
        new_arr[i] = malloc(sizeof(char) * (my_strlen(array[i]) + 1));
    arraydup(new_arr, array);
    new_arr[old_lenght] = strdup(str);
    new_arr[old_lenght + 1] = NULL;
    free_arr(array);
    return new_arr;
}

char** array_remove(int position, char** array)
{
    int i;
    char** new_array = malloc(sizeof(char*) * tablen(array));
    for (i = 0; i < position; i++)
        new_array[i] = array[i];
    for (i = position + 1; array[i]; i++)
        new_array[i - 1] = array[i];
    new_array[i - 1] = NULL;
    return new_array;
}
