/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** print_array
*/

#include <stdio.h>

void print_array(char** array)
{
    for (int i = 0; array[i]; i++) {
        printf("%s\n", array[i]);
    }
}
