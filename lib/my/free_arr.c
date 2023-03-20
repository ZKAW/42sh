/*
** EPITECH PROJECT, 2022
** BSQ
** File description:
** free_arr.c
*/

#include <stdlib.h>
#include "my.h"

int free_arr(char** array)
{
    int i = 0;
    for (i = 0; array[i] != NULL; i++) {
        free(array[i]);
    }
    free(array[i]);
    free(array);
    return 0;
}

int free_int_arr(int** array, int height)
{
    for (int i = 0; i < height; i++)
        free(array[i]);
    free(array);
    return 0;
}
