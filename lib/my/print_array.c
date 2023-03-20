/*
** EPITECH PROJECT, 2022
** my_ls
** File description:
** print_array.c
*/

#include "my.h"
#include <unistd.h>

void print_array(char** array)
{
    for (int i = 0; array[i] != NULL; i++) {
        write(1, array[i], my_strlen(array[i]));
        my_putchar('\n');
    }
}

void print_int_array(int** array, int row_size, int col_size)
{
    for (int row = 0; row < row_size; row++) {
        for (int col = 0; col < col_size; col++)
            my_printf("%d, ", array[row][col]);
        my_printf("\n");
    }
}
