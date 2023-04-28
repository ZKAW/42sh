/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** arraydup
*/

#include <stdlib.h>
#include <string.h>

int tablen(char **tab);

void arraydup(char** dest, char** src)
{
    for (int i = 0; src[i] != NULL; i++)
        dest[i] = strdup(src[i]);
    dest[tablen(src)] = NULL;
}
