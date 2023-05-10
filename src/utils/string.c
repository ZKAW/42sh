/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** string
*/

#include "../../include/mysh.h"

int is_char_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

char *skip_whitespace(char *str)
{
    while (is_char_whitespace(*str))
        str++;
    return str;
}

char *skip_non_whitespace(char *str)
{
    while (*str && !is_char_whitespace(*str))
        str++;
    return str;
}

extern int arrlen(char **arr)
{
    int i;

    for (i = 0; arr[i]; ++i);
    return i;
}

extern int full_arrlen(char **arr)
{
    int total = 0;
    int i;

    for (i = 0; arr[i]; ++i)
        total += strlen(arr[i]);
    return total + i;
}
