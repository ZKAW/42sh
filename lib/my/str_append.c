/*
** EPITECH PROJECT, 2022
** pushswap
** File description:
** str_append.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "my.h"

char *str_append(char *str, const char *to_append)
{
    int len1 = my_strlen(str), len2 = my_strlen(to_append);
    char* new_str = malloc(sizeof(char) * (len1 + len2 + 1));
    my_strcpy(new_str, str);
    my_strcat(new_str, to_append);
    free(str);
    return new_str;
}
