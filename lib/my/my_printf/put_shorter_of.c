/*
** EPITECH PROJECT, 2022
** my_printf
** File description:
** put_shorter_of.c
*/

#include <stdarg.h>
#include "../my.h"
#include "functions.h"

void put_espace(int n, char v);

int my_round(double nb)
{
    double k = nb;
    nb = nb * 10;
    while (nb > 10) {
        nb = (int) nb % 10;
    }
    if (nb >= 5) {
        k++;
    }
    return (int) k;
}

int check_shorter_sharp(data_t* data)
{
    if (data->sharp) {
        my_putchar('.');
        return 1;
    }
    return 0;
}

int put_shorter(double nb, int ndigits, int missings_digits, data_t* data)
{
    char sci = data->flag == 'g' ? 'e' : 'E';
    int count = 0;
    if (missings_digits > 0) {
        my_put_float(nb, missings_digits);
    } else if (missings_digits == 0) {
        my_printf("%d", my_round(nb));
        check_shorter_sharp(data);
    } else {
        put_sci_write(nb, sci, ndigits - 1);
    }
}

int put_shorter_of(va_list args, data_t* data, int* total_count)
{
    double nb = va_arg(args, double);
    int ndigits = data->precision ? data->precision : 6, count = ndigits;
    int missings_digits = ndigits - count_digits((int) nb);
    char sign = nb < 0 ? '-' : '+';
    char blank = data->zero_filled ? '0' : ' ';
    count += data->sharp ? 1 : 0;
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
    put_shorter(nb, ndigits, missings_digits, data);
    return ndigits;
}
