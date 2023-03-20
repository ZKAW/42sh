/*
** EPITECH PROJECT, 2022
** pushswap
** File description:
** array_append.c
*/

#include "my.h"
#include <stdlib.h>

char** array_append(char** array, char* const str)
{
    int old_lenght = my_arraylen(array);
    char** new_arr = malloc(sizeof(char*) * (old_lenght + 2));
    for (int i = 0; array[i] != NULL; i++)
        new_arr[i] = malloc(sizeof(char) * (my_strlen(array[i]) + 1));
    my_arrcpy(new_arr, array);
    new_arr[old_lenght] = my_strdup(str);
    new_arr[old_lenght + 1] = NULL;
    free_arr(array);
    return new_arr;
}
