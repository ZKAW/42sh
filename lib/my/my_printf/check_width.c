/*
** EPITECH PROJECT, 2022
** my_printf
** File description:
** check_width.c
*/

#include "functions.h"
#include "../my.h"

void put_espace(int n, char v);

void check_width(char* format, int position, data_t* data)
{
    char prevChar = format[position - 1];
    char c = format[position];
    int width = 0;
    if (data->width || data->left_justify)
        return;
    if ((!is_number(prevChar) || prevChar == '0') && prevChar != '.')
        width = my_getnbr(&format[position]);
    if (width > 0)
        data->width = width;
}

void oct_hex_width(data_t* data, int size)
{
    char vide = data->zero_filled ? '0' : ' ';
    if (data->width) {
        put_espace(data->width - size, vide);
    }
}
