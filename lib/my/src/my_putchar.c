/*
** EPITECH PROJECT, 2022
** my_putchar.c
** File description:
** Put char with write
*/

#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}
