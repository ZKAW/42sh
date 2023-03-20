/*
** EPITECH PROJECT, 2022
** my_printf
** File description:
** check_flags.c
*/

#include <stdio.h>
#include "functions.h"

static char under_flags[] = {'*', '-', '.', '#', '+', '0', ' '};

static char flags[18] = {'c', 'd', 'i', 's', '%', 'o',
    'x', 'X', 'u', 'f', 'e', 'E', 'g', 'G', 'p', 'n', 'b', 'S'};

int is_flag(char c)
{
    for (int i = 0; flags[i] != '\0'; i++)
        if (c == flags[i])
            return 1;
    return 0;
}

int get_underflag(char c)
{
    for (int i = 1; under_flags[i] != '\0'; i++)
        if (c == under_flags[i])
            return i;
    return 0;
}

int is_valid_flag(char c, data_t* data)
{
    if (data->blank == 1 && c == ' ')
        return 0;
    if ((c >= '0' && c <= '9') || get_underflag(c) || is_flag(c))
        return 1;
    return 0;
}

int valid_struct(data_t* data)
{
    if (data->width == -1 || data->precision == -1 || data->left_justify == -1
    || data->zero_filled == -1 || data->show_sign == -1 || data->blank == -1
    || data->sharp == -1 || !is_flag(data->flag))
        return 0;
    else
        return 1;
}
