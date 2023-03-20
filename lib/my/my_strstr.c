/*
** EPITECH PROJECT, 2022
** my_strstr.c
** File description:
** task05
*/

#include <stddef.h>
#include "my.h"

char* check_compare(char* str, char* to_find, int size)
{
    int difference;
    int i;
    for (i = 0; str[i] != to_find[0] && str[i] != '\0'; i++);
    if (str[i + 1] == '\0')
        return NULL;
    difference = my_strncmp(&str[i], to_find, size);
    if (difference == 0)
        return &str[i];
    else
        return check_compare(&str[++i], to_find, size);
}

char* my_strstr(char* str, char* const to_find)
{
    int size = my_strlen(to_find);
    return check_compare(str, to_find, size);
}
