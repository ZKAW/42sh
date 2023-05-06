/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** str_append
*/

#include <stdlib.h>
#include <string.h>

char *str_append(char *str, const char *to_append)
{
    size_t len1 = strlen(str);
    size_t len2 = strlen(to_append);

    char* new_str = malloc(sizeof(char) * (len1 + len2 + 1));
    strcpy(new_str, str);
    strcat(new_str, to_append);
    free(str);

    return (new_str);
}
