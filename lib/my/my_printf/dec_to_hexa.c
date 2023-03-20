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

int check_hexa_sharp(data_t* data)
{
    if (data->sharp) {
        my_putchar('0');
        my_putchar(data->flag);
        return 2;
    }
    return 0;
}

int dec_to_hex(va_list args, data_t* data, int* total_count)
{
    int count = 0, i = 0, letter = (data->flag == 'x') ? 87 : 55;
    long mod, quotient = va_arg(args, long);
    char octalNum[100];
    if (quotient == 0) {
        my_putchar('0');
        return 1;
    }
    for (i = 0; quotient > 0; i++) {
        mod = quotient % 16;
        octalNum[i] = mod + (mod < 10 ? '0' : letter);
        quotient = quotient / 16;
    }
    count += check_hexa_sharp(data);
    count += my_strlen(octalNum);
    oct_hex_width(data, count);
    for (i--; i >= 0; i--) {
        my_putchar(octalNum[i]);
    }
    return count;
}
