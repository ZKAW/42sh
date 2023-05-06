/*
** EPITECH PROJECT, 2023
** myradar
** File description:
** my_strdup
*/

#include "lib.h"
#include <stdlib.h>

char *my_strdup(char const *src)
{
    if (src == NULL) return (NULL);
    int len = my_strlen(src);
    char *dest = malloc(sizeof(char) * (len + 1));

    if (dest == NULL) return (NULL);
    for (int i = 0; i < len; i++)
        dest[i] = src[i];
    dest[len] = '\0';
    return (dest);
}

char *my_strndup(char const *src, int n)
{
    if (src == NULL) return (NULL);
    char *dest = malloc(sizeof(char) * (n + 1));

    if (dest == NULL) return (NULL);
    for (int i = 0; i < n && src[i]; i++)
        dest[i] = src[i];
    dest[n] = '\0';
    return (dest);
}
