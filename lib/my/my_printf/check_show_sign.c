/*
** EPITECH PROJECT, 2022
** my_printf
** File description:
** check_show_sign.c
*/

#include <stdarg.h>
#include <stdio.h>
#include "../my.h"
#include "functions.h"

void check_show_sign(char* format, int position, data_t* data)
{
    if (data->precision == 0)
        data->show_sign = 1;
    else
        data->show_sign = -1;
}
