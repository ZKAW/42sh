/*
** EPITECH PROJECT, 2022
** my_printf
** File description:
** my_printf.c
*/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "my.h"
#include "my_printf/functions.h"

void check_zero_filled(char* format, int position, data_t* data);
void check_precision(char* format, int position, data_t* data);
void check_show_sign(char* format, int position, data_t* data);
void check_sharp(char* format, int position, data_t* data);
void parse_alignment(char* format, int position, data_t* data);
void check_width(char* format, int i, data_t* data);
void check_blank(char* format, int position, data_t* data);
data_t* create_data(void);
int is_valid_flag(char c, data_t* data);
int get_underflag(char c);
int is_flag(char c);
void put_espace(int n, char v);
int valid_struct(data_t* data);
void put_espace(int n, char v);
void put_alignement(data_t* data, int len);

static char under_flags[] = {'*', '-', '.', '#', '+', '0', ' '};

static char flags[20] = {'c', 'd', 'i', 's', '%', 'o',
    'x', 'X', 'u', 'f', 'e', 'E', 'g', 'G', 'p', 'n', 'b', 'S', 'A', 'a'};

int get_valist_length(const char* format)
{
    int count = 0;
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%' && is_flag(format[i + 1])) {
            i++;
            count++;
        }
    }
    return count;
}

void choose_format(data_t* data, va_list args, int* count)
{
    int format_len = 0;
    int (*flags_functions[20])(va_list args, data_t* data, int* total_count) = {
        put_va_char, put_va_nbr, put_va_nbr, put_va_str, print_percent,
        dec_to_octal, dec_to_hex, dec_to_hex, my_put_big_int, my_put_va_float,
        put_va_sci_write, put_va_sci_write, put_shorter_of, put_shorter_of,
        put_adress, set_count, unsigned_to_bin, put_secure_str,
        put_hexa_float, put_hexa_float};
    for (int i = 0; flags[i] != '\0'; i++) {
        if (flags[i] == data->flag) {
            format_len = flags_functions[i](args, data, count);
            *count += format_len;
            put_alignement(data, format_len);
            break;
        }
    }
}

data_t* store_flags(char* format)
{
    data_t* data = create_data();
    int left_justify = 0, i = 0;
    void (*under_flags[])(char* format, int position, data_t* data) = {
        parse_alignment, parse_alignment, check_precision, check_sharp,
        check_show_sign, check_zero_filled, check_blank};
    for (i; is_valid_flag(format[i], data) && format[i] != '\0'; i++) {
        if (get_underflag(format[i])) {
            under_flags[get_underflag(format[i])](format, i, data);
            continue;
        }
        if (is_number(format[i]) && format[i] != '\0') {
            check_width(format, i, data);
        }
        if (is_flag(format[i])) {
            data->flag = format[i];
            data->len = i + 1;
            break;
        }
    }
    return data;
}

int check_printable(data_t* data, va_list args, int* count)
{
    if (valid_struct(data)) {
        choose_format(data, args, count);
        return data->len;
    }
    my_putchar('%');
    return 0;
}

int my_printf(char* format, ...)
{
    va_list args;
    data_t* data = NULL;
    int count = 0, i = 0, arg_size = get_valist_length(format);
    va_start(args, format);
    for (i; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            data = store_flags(&format[i + 1]);
            i += check_printable(data, args, &count);
        } else{
            my_putchar(format[i]);
            count++;
        }
    }
    free(data);
    va_end(args);
    return count;
}
