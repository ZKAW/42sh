/*
** EPITECH PROJECT, 2022
** my_printf
** File description:
** print_percent.c
*/

#include <stdarg.h>
#include "functions.h"


void my_putchar(char c);

int print_percent(va_list args, data_t* data, int* total_count)
{
    my_putchar('%');
    return 1;
}
