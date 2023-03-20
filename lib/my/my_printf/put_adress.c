/*
** EPITECH PROJECT, 2022
** my_printf
** File description:
** put_adress.c
*/

#include <stdarg.h>
#include "../my.h"
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

int my_printf(char* format, ...);

int put_adress(va_list args, data_t* data, int* total_count)
{
    long adress = va_arg(args, long);
    int count = my_printf("0x%x", adress);
    return count;
}
