/*
** EPITECH PROJECT, 2022
** my_printf
** File description:
** put_va_nbr.c
*/

#include <stdarg.h>
#include "functions.h"
#include "../my.h"

int my_put_nbr(int nb);
void put_espace(int n, char v);

int put_va_nbr(va_list args, data_t* data, int* total_count)
{
    int nb = va_arg(args, int);
    int count = count_digits(nb);
    char sign = nb < 0 ? '-' : '+';
    char blank = data->zero_filled ? '0' : ' ';
    if ((data->show_sign && nb > 0) || (nb < 0)) {
        count++;
        if (data->zero_filled) {
            my_putchar(sign);
            put_espace(data->width - count, blank);
        } else {
            put_espace(data->width - count, blank);
            my_putchar(sign);
        }
    } else
        put_espace(data->width - count, blank);
    nb = nb < 0 ? nb * -1 : nb;
    my_put_nbr(nb);
    return count;
}
