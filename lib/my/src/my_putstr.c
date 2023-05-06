/*
** EPITECH PROJECT, 2022
** my_putstr.c
** File description:
** disp string char one by one
*/

#include <unistd.h>

void my_putstr(char const *str, int std)
{
    for (int i = 0; str[i] != '\0'; i++)
        write(std, &str[i], 1);
}
