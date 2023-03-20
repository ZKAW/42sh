/*
** EPITECH PROJECT, 2022
** my_printf
** File description:
** check_precision.c
*/

#include "functions.h"

int my_getnbr(char const *str);

void check_precision(char* format, int position, data_t* data)
{
    data->precision = my_getnbr(&format[position]);
}
