/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** input
*/

#include "mysh.h"

char **tokenize_string(char *input, char *sep)
{
    char *input_dup = strdup(input);
    char **parsed = malloc(sizeof(char *) * (strlen(input_dup) + 1));
    int i = 0;
    char *token = strtok(input_dup, sep);

    while (token != NULL) {
        parsed[i] = clean_str(strdup(token));
        token = strtok(NULL, sep);
        i++;
    }
    parsed[i] = NULL;
    free(input_dup);

    return (parsed);
}

char *copy_until(char *dst, char *src, char *delim)
{
    while (*src && !strchr(delim, *src))
        *(dst++) = *(src++);
    *dst = '\0';
    return src;
}
