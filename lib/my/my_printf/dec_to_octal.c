/*
** EPITECH PROJECT, 2022
** my_printf
** File description:
** dec_to_octal.c
*/

#include <stdarg.h>
#include "functions.h"

void my_putchar(char c);
int my_strlen(char* str);
void oct_hex_width(data_t* data, int size);

int check_octal_sharp(data_t* data)
{
    if (data->sharp) {
        my_putchar('0');
        return 1;
    }
    return 0;
}

int dec_to_octal(va_list args, data_t* data, int* total_count)
{
    int octalnb, count = 0, i = 0, nb = va_arg(args, int);
    char octalNum[100];
    if (nb == 0) {
        oct_hex_width(data, 1);
        my_putchar('0');
        return 1;
    }
    while (nb != 0) {
        octalNum[i] = '0' + (nb % 8);
        nb = nb / 8;
        i++;
    }
    i--;
    count += check_octal_sharp(data) + i + 1;
    oct_hex_width(data, count);
    for (i; i >= 0; i--) {
        my_putchar(octalNum[i]);
    }
    return count;
}
