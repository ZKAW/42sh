/*
** EPITECH PROJECT, 2023
** myradar
** File description:
** my_atoi
*/

#include "lib.h"

static int is_c_digit(int c)
{
    return (c >= '0' && c <= '9');
}

int my_atoi(const char *str)
{
    int result = 0;
    int sign = 1;

    while (is_c_space(*str)) str++;

    if (*str == '+' || *str == '-') {
        if (*str == '-') {
            sign = -1;
        }
        str++;
    }

    while (is_c_digit(*str)) {
        result = result * 10 + (*str - '0');
        str++;
    }

    return (sign * result);
}
