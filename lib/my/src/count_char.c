/*
** EPITECH PROJECT, 2023
** lib
** File description:
** count_char
*/

#include "lib.h"

int count_char(char *str, char c)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == c)
            count++;
    return (count);
}
