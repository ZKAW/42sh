/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** render.c
*/

#include "mysh.h"

void print_string(string_t* string)
{
    for (int i = 0; i < string->len; i++)
        dprintf(1, "%c", string->str[i]);
}

int check_history(char* dest, char* src, shell_t* shell)
{
    string_t* last = shell->history.head;
    if (strncmp(src, "!!", 2))
        return 0;
    if (last == NULL) {
        dprintf(2, "0: Event not found.\n");
        return -1;
    }
    strncpy(dest, last->str, last->len - 1);
    return last->len - 1;
}

char* merge_string(string_t* string, shell_t* shell)
{
    char buffer[4096] = {0};
    int position = 0, history = 0;
    for (int i = 0; i < string->len; i++) {
        history = check_history(buffer + position, string->str + i, shell);
        switch (history) {
        case 0: break;
        case -1: return NULL;
        default:
            position += history;
            i++;
            continue;
        }
        buffer[position++] = string->str[i];
    }
    buffer[position] = '\0';
    string->len = position;
    for (int i = 0; i < position; i++)
        string->str[i] = buffer[i];
    string->str[position] = '\n';
    return strdup(buffer);
}
