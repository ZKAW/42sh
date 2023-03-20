/*
** EPITECH PROJECT, 2022
** my_printf
** File description:
** unsigned_to_bin.c
*/

#include <stdarg.h>
#include "../my.h"
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

int unsigned_to_bin(va_list args, data_t* data, int* total_count)
{
    unsigned int nb = va_arg(args, unsigned int);
    unsigned int temp_nb = nb;
    int i = 0;
    int digits[100];
    for (i; temp_nb > 0; i++) {
        digits[i] = temp_nb % 2;
        temp_nb = temp_nb / 2;
    }
    for (i--; i >= 0; i--)
        my_put_nbr(digits[i]);
    return 0;
}
