/*
** EPITECH PROJECT, 2023
** myradar
** File description:
** my_strtok
*/

#include "lib.h"
#include <unistd.h>

char *my_strpbrk(char *str, char *accept)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (my_strchr(accept, str[i]) != NULL) {
            return (str + i);
        }
    }
    return (NULL);
}

char *my_strtok(char *str, const char *delim)
{
    static char *s = NULL;
    char *end;

    if (str != NULL)
        s = str;

    if (s == NULL)
        return NULL;

    end = my_strpbrk(s, (char *) delim);
    if (end == NULL) {
        char *temp = s;
        s = NULL;
        return temp;
    }

    *end = '\0';
    char *temp = s;
    s = end + 1;
    return temp;
}
