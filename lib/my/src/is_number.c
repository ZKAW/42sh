/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** is_number
*/

#include <stdlib.h>

int is_number(char *str)
{
    int i = 0;

    if (str == NULL)
        return (0);
    if (str[0] == '-')
        i++;
    for (; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return (0);
    }
    return (1);
}
