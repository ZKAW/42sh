/*
** EPITECH PROJECT, 2022
** my_putstr.c
** File description:
** task02
*/

#include <unistd.h>
#include "./my.h"

int my_putstr(char const *str)
{
    int len = my_strlen(str);
    write(1, str, len);
    return my_strlen(str);
}
