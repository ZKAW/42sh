/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** parser_tokens.c
*/

#include "../../include/mysh.h"

void error(char *msg)
{
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

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

char *copy_until(char *dst, char *src, char *delim)
{
    while (*src && !strchr(delim, *src))
        *(dst++) = *(src++);
    *dst = '\0';
    return src;
}
