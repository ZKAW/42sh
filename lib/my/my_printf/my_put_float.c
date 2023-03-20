/*
** EPITECH PROJECT, 2022
** my_printf
** File description:
** my_put_float.c
*/

#include <stdarg.h>
#include "../my.h"
#include "functions.h"

void put_espace(int n, char v);

void print_nzero(int n)
{
    for (int j = 0; j < n; j++)
        my_putchar('0');
}

static void check_trailing(double* decimals)
{
    int trailing = (*decimals - (int) *decimals) * 10;
    if (trailing >= 5)
        *decimals = *decimals + 1;
}

void fill_zeros(float decimals, int pow)
{
    long firsts_dig = (long) decimals;
    firsts_dig = firsts_dig == 0 ? 1 : firsts_dig;
    int i = 0;
    for (i; firsts_dig < pow; i++) {
        firsts_dig = firsts_dig * 10;
    }
    print_nzero(i - 1);
}

int my_put_float(double nb, int power)
{
    double decimals = 0;
    int i = 0, count = 0, pow = my_compute_power_rec(10, power);
    if ( nb < 0 ) {
        my_putchar('-');
        count++;
        nb = - nb;
    }
    for (i; (nb - i) >= 1; i++);
    nb = nb - i;
    count += my_put_nbr(i);
    my_putchar('.');
    if (nb == 0) {
        print_nzero(power);
        return count + 7;
    }
    decimals = nb * pow;
    fill_zeros(decimals, pow);
    check_trailing(&decimals);
    my_put_nbr(decimals);
    return count + 7;
}

int my_put_va_float(va_list args, data_t* data, int* total_count)
{
    double nb = va_arg(args, double);
    int precision = data->precision ? data->precision : 6;
    char sign = nb < 0 ? '-' : '+';
    char blank = data->zero_filled ? '0' : ' ';
    int count = count_digits((int) nb) + 1;
    count += precision;
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
    my_put_float(nb, precision);
    return count;
}
