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
    char_t* after = string->after, *character = string->after;
    int i = 0 , j = 0, k = 0;
    while (after) {
        after = after->next;
        i++;
    }
    j = i,
    k = i;
    while (i-- >= 0)
        dprintf(1, "\x1b[C");
    while (j-- >= 0)
        dprintf(1, "\b \b");
    while (character) {
        dprintf(1, "%c", character->c);
        character = character->next;
    }
    while (k-- > 0)
        dprintf(1, "\033[1D");
}

int handle_backspace(char c, string_t* string)
{
    char_t* before = string->before, *character;
    int i = 0;
    if (c == '\x7f') {
        if (string->before) {
            dprintf(1, "\b \b");
            string->after = string->before->next;
            string->before = string->before->prev;
            if (string->before)
                string->before->next = string->after;
            else
                string->first = string->after;
            delete_chars(string);
        }
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
