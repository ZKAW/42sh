/*
** EPITECH PROJECT, 2022
** my_printf
** File description:
** parse_alignement.c
*/

#include <stdlib.h>
#include "../my.h"
#include "functions.h"

int is_flag(char c);
void put_espace(int n, char v);
void parse_alignment(char* format, int position, data_t* data)
{
    int i = 0;
    int result = 0;
    char* limit;
    char* str = &format[position];
    for (i; str[i] != '.' && str[i] != '\0' && !is_flag(str[i]) ; i++);
    limit = malloc(sizeof(char) * (i + 1));
    my_strncpy(limit, str, i);
    data->left_justify = my_getnbr(limit);
}

void put_alignement(data_t* data, int len)
{
    if (data->flag == '%')
        return;
    int size = data->left_justify;
    size = size < 0 ? -size : size;
    put_espace(size - len, ' ');
}
