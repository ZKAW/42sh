/*
** EPITECH PROJECT, 2022
** my_strstr.c
** File description:
** find str in str (get everything after specific str)
*/

#include <unistd.h>

char *my_strstr(char *str, char const *to_find)
{
    while (*str != '\0') {
        if (*str == *to_find) {
            return (str);
        }
        str++;
    }

    return (NULL);
}
