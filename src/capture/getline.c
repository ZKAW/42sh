/*
** EPITECH PROJECT, 2022
** mini-shell2
** File description:
** getline.c
*/

#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <time.h>
#include "../../include/my.h"
#include "../../include/string.h"
#include "../../include/mini_shell.h"

int handle_commands(char c, shell_t* shell);
void disable_raw_mode(struct termios* raw);
void enable_raw_mode(struct termios* raw);


void handle_regular_char(shell_t* shell, char c)
{
    int i = 0;
    char_t* character;
    char* str;
    string_t* string = shell->history;
    append_string(c, string);
    str = string->str + string->position;
    dprintf(1, "%c", c);
    while (str[i]) {
        dprintf(1, "%c", str[i]);
        i++;
    }
    while (i > 0) {
        dprintf(1, "\033[1D");
        i--;
    }
}

char* end_of_line(shell_t* shell)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    dprintf(1, "%c", '\n');
    sprintf(shell->history->hour, "%d:%d", tm.tm_hour, tm.tm_min);
    disable_raw_mode(&shell->term);
    return merge_string(shell->history);
}

char* my_getline(shell_t* shell)
{
    char c;
    int valread = 0;
    shell->history = create_string(shell);
    enable_raw_mode(&shell->term);
    for (;;) {
        valread = read(0, &c, 1);
        if (valread < 0)
            continue;
        if (c == '\n')
            return end_of_line(shell);
        if (handle_commands(c, shell))
            continue;
        handle_regular_char(shell, c);
    }
    return NULL;
}
