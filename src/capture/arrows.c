/*
** EPITECH PROJECT, 2022
** mini-shell2
** File description:
** arrows.c
*/

#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include "line.h"
#include "mysh.h"

void copy_string(string_t* dest, string_t* src);

void left_arrow(shell_t* shell)
{
    string_t* string = shell->string;
    if (string->position == 0)
        return;
    string->position--;
    dprintf(1, "%s", "\x1b[D");
}

void right_arrow(shell_t* shell)
{
    string_t* string = shell->string;
    if (string->position == string->len)
        return;
    string->position++;
    dprintf(1, "%s", "\x1b[C");
}

void up_arrow(shell_t* shell)
{
    string_t* string = shell->string;
    history_t* history = &shell->history;
    if ((!history->current && !history->head)
    || (history->current && !history->current->next))
        return;
    history->current = history->current ?
    history->current->next : history->head;
    copy_string(string, history->current);
    dprintf(1, "\x1b[2K\r");
    my_putstr(get_prompt_prefix(), 1);
    print_string(shell->string);
}

void down_arrow(shell_t* shell)
{
    string_t* string = shell->string;
    history_t* history = &shell->history;
    if (!history->current)
        return;
    if (history->current->prev) {
        history->current = history->current->prev;
        copy_string(string, history->current);
    } else {
        history->current = NULL;
        string->len = 0;
        string->position = 0;
        string->str[0] = '\0';
    }
    dprintf(1, "\x1b[2K\r");
    my_putstr(get_prompt_prefix(), 1);
    print_string(shell->string);
}

int handle_arrows(shell_t* shell)
{
    char arrow[3];
    char arrows[4] = {'A', 'B', 'C', 'D'};
    void (*arrows_func[4])(shell_t*) = {up_arrow, down_arrow, right_arrow,
        left_arrow};
    if (read(STDIN_FILENO, &arrow[0], 1) == -1)
        return 0;
    if (read(STDIN_FILENO, &arrow[1], 1) == -1)
        return 0;
    if (arrow[0] != '[')
        return 1;
    for (int i = 0; i < 4; i++) {
        if (arrow[1] == arrows[i]) {
            arrows_func[i](shell);
            return 1;
        }
    }
    return 1;
}
