/*
** EPITECH PROJECT, 2022
** my.h
** File description:
** task02
*/

#include <stddef.h>

#ifndef _MY_H_
    #define _MY_H_

        void my_putchar(char c);
        int is_number(char c);
        int count_digits(int nb);
        char* my_strstr(char* str, char* const to_find);
        int my_isneg(int nb);
        int my_strcmp(char const *s1, char const *s2);
        int my_put_nbr(int nb);
        int my_strncmp(char const *s1, char const *s2, int n);
        void my_swap(int *a, int *b);
        char *my_strupcase(char *str);
        int my_putstr(char const *str);
        char *my_strlowcase(char *str);
        int my_strlen(char const *str);
        char* merge_array(char** array);
        char *my_strcapitalize(char *str);
        long my_getnbr(char const *str);
        int my_str_isalpha(char const *str);
        void my_sort_int_array(int *tab, int size);
        int my_str_isnum(char const *str);
        int my_compute_power_rec(int nb, int power);
        int my_str_islower(char const *str);
        int my_compute_square_root(int nb);
        int my_str_isupper(char const *str);
        int my_is_prime(int nb);
        int my_str_isprintable(char const *str);
        int my_find_prime_sup(int nb);
        int my_showstr(char const *str);
        void print_array(char** array);
        char** string_split(char const * str, char* separator);
        int my_arraylen(char** array);
        int free_int_arr(int** array, int height);
        int free_arr(char** array);
        char *my_strcpy(char *dest, char const *src);
        char** array_remove(int position, char** array);
        int my_showmem(char const *str, int size);
        char *my_strncpy(char *dest, char const *src, int n);
        char* load_file_in_mem(char const * filepath);
        void my_strcat(char *dest, char const *src);
        char *my_revstr(char *str);
        int is_include(char to_find, char *str);
        char *my_strncat(char *dest, char const *src, int nb);
        char** my_str_to_word_array(char* str, char* delim);
        int count_long_digits(long nb);
        int is_alpha(char c);
        char *my_realloc(char* str, size_t size);
        char get_lowerchar(char c);
        void print_int_array(int** array, int row_size, int col_size);
        int my_printf(char *format, ...);
        char** my_arrcpy(char **dest, char **src);
        char** array_append(char** array, char* const str);
        char* my_strdup(const char* str);
        char *str_append(char *str, const char *to_append);
#endif /* _MY_H_ */
