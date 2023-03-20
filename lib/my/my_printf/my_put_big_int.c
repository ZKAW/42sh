/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** my_put_big_int.c
*/

#include "../my.h"
#include <stdarg.h>
#include "functions.h"

int my_put_big_int(va_list args, data_t* data, int* total_count)
{
    unsigned int nb = va_arg(args, unsigned int);
    int i = 0;
    int ndigits = 0;
    int digits[100];

    if (nb == 0) {
        my_putchar('0');
        return 1;
    }
    for (i; nb != 0; i++) {
        digits[i] = nb % 10;
        nb = nb / 10;
    }
    ndigits = i;
    i--;
    for (i; i >= 0; i--) {
        my_putchar(digits[i] + '0');
    }
    return ndigits;
}
