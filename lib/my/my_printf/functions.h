/*
** EPITECH PROJECT, 2022
** my_printf
** File description:
** functions.h
*/

#include <stdarg.h>

#ifndef _FUNCTIONS_H_
    #define _FUNCTIONS_H_

        typedef struct printf_data {
            int width;
            int precision;
            int left_justify;
            int zero_filled;
            int show_sign;
            int blank;
            int sharp;
            char flag;
            int len;
        } data_t;

        // FAIT %c COUNT BON
        int put_va_char(va_list args, data_t* data, int* total_count);
        // FAIT %d %i COUNT BON
        int put_va_nbr(va_list args, data_t* data, int* total_count);
        // FAIT %s COUNT BON
        int put_va_str(va_list args, data_t* data, int* total_count);
        // FAIT %% COUNT BON
        int print_percent(va_list args, data_t* data, int* total_count);
        // FAIT %o COUNT BON
        int dec_to_octal(va_list args, data_t* data, int* total_count);
        // FAIT %x %X
        int dec_to_hex(va_list args, data_t* data, int* total_count);
        // FAIT %u
        int my_put_big_int(va_list args, data_t* data, int* total_count);
        // FAIT LETSGO %f
        int my_put_va_float(va_list args, data_t* data, int* total_count);
        int my_put_float(double nb, int power);
        // FAIT %n
        int set_count(va_list args, data_t* data, int* total_count);
        // fait ?? %e %E
        int put_va_sci_write(va_list args, data_t* data, int* total_count);
        int put_sci_write(double nb, char flag, int precision);
        // FAIT %b
        int unsigned_to_bin(va_list args, data_t* data, int* total_count);
        // FAIT %p
        int put_adress(va_list args, data_t* data, int* total_count);
        //%g %G ??????
        int put_shorter_of(va_list args, data_t* data, int* total_count);
        //%S
        int put_secure_str(va_list args, data_t* data, int* total_count);
        int put_hexa_float(va_list args, data_t* data, int* total_count);
#endif
