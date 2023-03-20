/*
** EPITECH PROJECT, 2022
** my_printf
** File description:
** check_zero_filled.c
*/

#include <stdarg.h>
#include <stdio.h>
#include "../my.h"
#include "functions.h"

void check_zero_filled(char* format, int position, data_t* data)
{
    int prev = format[position - 1];
    if (is_number(prev))
        return;
    if (data->precision == 0) {
        data->zero_filled = 1;
    } else
        data->zero_filled = -1;
}
