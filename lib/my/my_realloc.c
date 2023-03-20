/*
** EPITECH PROJECT, 2022
** my_ls
** File description:
** my_realloc.c
*/

#include <stddef.h>
#include <stdlib.h>

static void* x_memset(int c, size_t nmemb, size_t size)
{
    char *tmp = malloc(size * (nmemb + 1));
    size_t i = 0;
    if (tmp == NULL)
        return (NULL);
    while (i <= nmemb) {
        tmp[i] = c;
        ++i;
    }
    return (tmp);
}

char* my_realloc(char* str, size_t size)
{
    char* new_str = x_memset(0, size + 1, sizeof(char));
    if (str == NULL || new_str == NULL || size < 1)
        return (NULL);
    for (int i = 0; str[i] != '\0'; i++)
        new_str[i] = str[i];
    free(str);
    return new_str;
}
