/*
** EPITECH PROJECT, 2022
** mini-shell1
** File description:
** array_remove.c
*/

#include <stddef.h>
#include <stdlib.h>
#include "my.h"

char** array_remove(int position, char** array)
{
    int i;
    char** new_array = malloc(sizeof(char*) * my_arraylen(array));
    for (i = 0; i < position; i++)
        new_array[i] = array[i];
    for (i = position + 1; array[i]; i++)
        new_array[i - 1] = array[i];
    new_array[i - 1] = NULL;
    return new_array;
}
