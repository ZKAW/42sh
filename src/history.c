/*
** EPITECH PROJECT, 2022
** mini-shell2
** File description:
** history.c
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "mysh.h"

char * strdup( const char * source );

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

char* get_last_command(shell_t* shell)
{
    char command[4096] = {0};
    string_t* string = shell->history.head;
    if (string == NULL)
        return NULL;
    for (int i = 0; i < string->len - 1; i++)
        command[i] = string->str[i];
    return strdup(command);
}
