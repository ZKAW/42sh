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
    string->first = NULL;
    string->last = NULL;
    string->before = NULL;
    string->after = NULL;
    string->next = shell->history;
    string->prev = NULL;
    string->hour[0] = '\0';
    if (shell->history)
        shell->history->prev = string;
    shell->history = string;
    return string;
}

char_t* append_string(char c, string_t* string)
{
    char_t* character = malloc(sizeof(char_t));
    character->c = c;
    character->prev = string->before;
    character->next = string->after;
    if (character->next)
        character->next->prev = character;
    if (character->prev)
        character->prev->next = character;
    if (character->prev == NULL)
        string->first = character;
    if (character->next == NULL)
        string->last = character;
    string->before = character;
    return character;
}

void print_string(string_t* string)
{
    char_t* character = string->first;
    while (character) {
        dprintf(1, "%c", character->c);
        character = character->next;
    }
}

char* merge_string(string_t* string)
{
    int len = 0, i = 0;
    char* str = NULL;
    char_t* character = string->first;
    while (character) {
        len++;
        character = character->next;
    }
    str = malloc(sizeof(char) * (len + 1));
    str[len] = '\0';
    character = string->first;
    while (character) {
        str[i++] = character->c;
        character = character->next;
    }
    return str;
}
