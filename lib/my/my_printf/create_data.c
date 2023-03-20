/*
** EPITECH PROJECT, 2022
** my_printf
** File description:
** create_data.c
*/

#include <stdlib.h>
#include "functions.h"

data_t* create_data(void)
{
    data_t* data = malloc(sizeof(data_t));
    data->blank = 0;
    data->flag = 0;
    data->left_justify = 0;
    data->len = 0;
    data->precision = 0;
    data->sharp = 0;
    data->show_sign = 0;
    data->width = 0;
    data->zero_filled = 0;
    return data;
}
