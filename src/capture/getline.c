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
    string_t* string = shell->history;
    append_string(c, string);
    dprintf(1, "%c", c);
    character = string->after;
    while (character) {
        dprintf(1, "%c", character->c);
        character = character->next;
        i++;
    }
    while (i > 0) {
        dprintf(1, "\033[1D");
        i--;
    }
}

char* copy_string_at_end_of_history(shell_t* shell)
{
    string_t* to_copy = shell->history;
    string_t* last = shell->history;
    char_t* character = to_copy->first;
    string_t* string = create_string(shell);
    dprintf(1, "on entre\n");
    while (character) {
        append_string(character->c, string);
        character = character->next;
    }
    while (last->next)
        last = last->next;
    last->next = string;
    string->prev = last;
    dprintf(1, "on sort\n");
}

char* end_of_line(shell_t* shell)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    shell->history->after = NULL;
    shell->history->before = shell->history->last;
    dprintf(1, "%c", '\n');
    if (my_strlen(shell->history->hour))
        copy_string_at_end_of_history(shell);
    sprintf(shell->history->hour, "%d:%d", tm.tm_hour, tm.tm_min);
    dprintf(1, "ah gros\n");
    disable_raw_mode(&shell->term);
    return merge_string(shell->history);
}

char* my_getline(shell_t* shell)
{
    string_t* string = create_string(shell);
    char_t* character = NULL;
    char c;
    int valread = 0;
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
