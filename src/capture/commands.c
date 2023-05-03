/*
** EPITECH PROJECT, 2022
** mini-shell2
** File description:
** commands.c
*/

#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include "../../include/my.h"
#include "../../include/string.h"
#include "../../include/mini_shell.h"


int handle_arrows(shell_t* shell);

void delete_chars(string_t* string)
{
    string->position--;
    string->len--;
    for (int i = string->position; i < string->len; i++)
        dprintf(1, LEFT);
    for (int i = string->position; i <= string->len; i++)
        dprintf(1, "\b \b");
    for (int i = string->position; i < string->len; i++)
        dprintf(1, "%c", string->str[i + 1]);
    for (int i = string->position; i < string->len; i++)
        dprintf(1, RIGHT);
    for (int i = string->position; i < string->len; i++)
        string->str[i] = string->str[i + 1];
}

int handle_backspace(char c, string_t* string)
{
    if (c == '\x7f') {
        if (string->position != 0 && string->len != 0)
            delete_chars(string);
        return 1;
    }
    return 0;
}

int handle_commands(char c, shell_t* shell)
{
    string_t* string = shell->history;
    if (handle_backspace(c, string))
        return 1;
    if (c == '\033') {
        if (handle_arrows(shell))
            return 1;
    }
    return 0;
}
