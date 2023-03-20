/*
** EPITECH PROJECT, 2022
** my_sokoban
** File description:
** my_arrcpy.c
*/

#include "my.h"

char** my_arrcpy(char **dest, char **src)
{
    int i = 0;
    for (i = 0; src[i] != NULL; i++) {
        my_strcpy(dest[i], src[i]);
    }
    dest[i] = NULL;
    return dest;
}
