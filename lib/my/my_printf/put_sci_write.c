/*
** EPITECH PROJECT, 2022
** my_printf
** File description:
** put_sci_write.c
*/

#include <stdarg.h>
#include "../my.h"
#include "functions.h"

static void check_trailing(double* decimals)
{
    int trailing = (*decimals - (int) *decimals) * 10;
    if (trailing >= 5)
        *decimals = *decimals + 1;
}

int put_sci_write(double nb, char flag, int precision)
{
    int exp = 0, count = 2;
    if (nb < 0) {
        my_putchar('-');
        nb = nb * -1;
        count++;
    }
    while (nb > 10) {
        nb = nb / 10;
        exp++;
    }
    count += my_put_float(nb, precision);
    my_putchar(flag);
    my_putchar('+');
    if (exp < 10)
        my_putchar('0');
        count++;
    count += my_put_nbr(exp);
    return count;
}

int put_va_sci_write(va_list args, data_t* data, int* total_count)
{
    int count = 0;
    double nb = va_arg(args, double);
    if (data->show_sign && nb > 0) {
        my_putchar ('+');
        count++;
    }
    count = put_sci_write(nb, data->flag, 6);
    return count;
}
