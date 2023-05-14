/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** string
*/

#include "../../include/mysh.h"

int have_space(char *str)
{
    int i = 0;
    for (; str[i] != '\0'; i++) {
        if (str[i] == ' ')
            return (1);
    }
    return (0);
}

int is_char_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

char *skip_whitespace(char *str)
{
    while (*str && is_char_whitespace(*str))
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
