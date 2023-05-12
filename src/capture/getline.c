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
#include <stdbool.h>
#include "mysh.h"

int handle_commands(char c, shell_t* shell);
void disable_raw_mode(struct termios* raw);
void enable_raw_mode(struct termios* raw);
string_t* get_string(string_t* string);
void sigint_handler(int sig);


void handle_regular_char(shell_t* shell, char c)
{
    int i = 0;
    char* str;
    string_t* string = shell->string;
    append_string(c, string);
    str = string->str + string->position;
    dprintf(1, "%c", c);
    while (i < string->len - string->position) {
        dprintf(1, "%c", str[i]);
        i++;
    }
    while (i > 0) {
        dprintf(1, "\033[1D");
        i--;
    }
}

ssize_t end_of_line(shell_t* shell, char **bufferptr)
{
    history_t* history = &shell->history;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    dprintf(1, "%c", '\n');
    shell->string->str[shell->string->len++] = '\n';
    sprintf(shell->string->hour, "%d:%d", tm.tm_hour, tm.tm_min);
    disable_raw_mode(&shell->term);
    history->position = 0;
    *bufferptr = merge_string(shell->string, shell);
    if (*bufferptr == NULL)
        return 1;
    shell->string->next = history->head;
    if (history->head)
        history->head->prev = shell->string;
    history->head = shell->string;
    history->current = NULL;
    return shell->string->len;
}

ssize_t my_getline(char **bufferptr, shell_t* shell)
{
    char c;
    int valread = 0;
    shell->string = get_string(create_string());
    signal(SIGINT, sigint_handler);
    enable_raw_mode(&shell->term);
    for (;;) {
        c = 0;
        valread = read(0, &c, 1);
        if (valread < 0 && c == 0)
            continue;
        if (c == '\004' && get_string(NULL)->len == 0)
            return -1;
        if (c == '\n')
            return end_of_line(shell, bufferptr);
        if (handle_commands(c, shell))
            continue;
        handle_regular_char(shell, c);
    }
    return 0;
}
