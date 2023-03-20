/*
** EPITECH PROJECT, 2022
** my_printf
** File description:
** put_va_char.c
*/

#include <stdarg.h>
#include "functions.h"

void my_putchar(char c);

int put_va_char(va_list args, data_t* data, int* total_count)
{
    char c = (char) va_arg(args, int);
    my_putchar(c);
    return 1;
}
