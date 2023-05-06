/*
** EPITECH PROJECT, 2022
** myradar
** File description:
** my_strcat
*/

#include <stdlib.h>
#include "lib.h"

char *my_strcat(char *dest, char const *src)
{
    int i = 0;
    int j = 0;

    while (dest[i] != '\0')
        i++;
    while (src[j] != '\0') {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
    return (dest);
}

char *my_strcat_c(char *str, char c)
{
    if (!str) {
        char *ap = malloc(2);
        ap[0] = c;
        ap[1] = '\0';
        return ap;
    }

    int len = 0;
    while (str[len] != '\0') len++;

    char *ap = malloc(len + 2);
    if (!ap) return NULL;

    my_strcpy(ap, str);
    ap[len] = c;
    ap[len +1 ] = '\0';

    free(str);
    return (ap);
}
