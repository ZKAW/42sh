/*
** EPITECH PROJECT, 2022
** my_ls
** File description:
** my_arraylen.c
*/

#include <stddef.h>

int my_arraylen(char** array)
{
    int i = 0;
    if (array == NULL || array[0] == NULL)
        return 0;
    for (i; array[i] != NULL; i++);
    return i;
}
