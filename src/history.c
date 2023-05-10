/*
** EPITECH PROJECT, 2022
** mini-shell2
** File description:
** history.c
*/

#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include "mysh.h"

void show_history(char** cmd UNUSED, shell_t* shell)
{
    int i = 1;
    string_t* string = shell->history.head;
    while (string->next)
        string = string->next;
    while (string) {
        dprintf(1, "\t%d %s\t", i, string->hour);
        print_string(string);
        my_putchar('\n');
        string = string->prev;
        i++;
    }
}