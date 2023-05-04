/*
** EPITECH PROJECT, 2022
** mini-shell2
** File description:
** arrows.c
*/

#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include "../../include/my.h"
#include "../../include/string.h"
#include "../../include/mini_shell.h"

void print_path(void);
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
    history->current = history->current ?
    history->current->next : history->head;
    copy_string(string, history->current);
    dprintf(1, "\x1b[2K\r");
    print_path();
    print_string(shell->string);
}

void down_arrow(shell_t* shell)
{
    string_t* string = shell->string;
    history_t* history = &shell->history;
    if (!history->current->prev)
        return;
    history->current = history->current->prev;
    copy_string(string, history->current);
    shell->history.position++;
    dprintf(1, "\x1b[2K\r");
    print_path();
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
