/*
** EPITECH PROJECT, 2022
** my_printf
** File description:
** put_va_str.c
*/

#include <stdarg.h>
#include "../my.h"
#include "functions.h"

void put_espace(int n, char v);
int my_putstr(char const *str);

int put_va_str(va_list args, data_t* data, int* total_count)
{
    char* str = va_arg(args, char*);
    int len = my_strlen(str);
    put_espace(data->width - len, ' ');
    my_putstr(str);
    return my_strlen(str);

}

void put_espace(int n, char v)
{
    int i = 0;
    for (i; i < n; i++)
    my_putchar(v);
}
