/*
** EPITECH PROJECT, 2023
** myradar
** File description:
** my_strchr
*/

#include <unistd.h>

char *my_strchr(char *str, char c)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == c)
            return (str + i);
        i++;
    }
    return (NULL);
}
