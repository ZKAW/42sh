/*
** EPITECH PROJECT, 2022
** PSU
** File description:
** string.c
*/

#include <stddef.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../../include/my.h"
#include "../../include/string.h"
#include "../../include/mini_shell.h"

string_t* create_string(shell_t* shell)
{
    string_t* string = malloc(sizeof(string_t));
    string->next = shell->history;
    string->prev = NULL;
    string->position = 0;
    string->len = 0;
    string->str[0] = '\0';
    string->hour[0] = '\0';
    if (shell->history)
        shell->history->prev = string;
    return string;
}

void append_string(char c, string_t* string)
{
    string->str[string->position++] = c;
    string->str[string->position] = '\0';
    string->len++;
}

void copy_string_at_end_of_history(shell_t* shell)
{
    string_t* to_copy = shell->history;
    string_t* last = shell->history;
    string_t* string = create_string(shell);
}

void print_string(string_t* string)
{
    for (int i = 0; i < string->len; i++)
        dprintf(1, "%c", string->str[i]);
}

char* merge_string(string_t* string)
{
    int i = 0;
    char* str = NULL;
    str = malloc(sizeof(char) * (string->len + 1));
    my_strncat(str, string->str, string->len);
    return str;
}
