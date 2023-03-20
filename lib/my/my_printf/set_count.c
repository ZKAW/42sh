/*
** EPITECH PROJECT, 2022
** my_printf
** File description:
** set_count.c
*/

#include <stdarg.h>
#include "functions.h"

int set_count(va_list args, data_t* data, int* total_count)
{
    int* adress = va_arg(args, int*);
    *adress = *total_count;
    return 0;
}
