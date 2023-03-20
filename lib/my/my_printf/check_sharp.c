/*
** EPITECH PROJECT, 2022
** my_printf
** File description:
** check_sharp.c
*/

#include <stdlib.h>
#include "functions.h"

void check_sharp(char* format, int position, data_t* data)
{
    if (data->precision == 0 &&
        data->width == 0 &&
        data->left_justify == 0) {
            data->sharp = 1;
    } else
        data->sharp = -1;
}
