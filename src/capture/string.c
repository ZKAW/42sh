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

#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

string_t* create_string(shell_t* shell)
{
    string_t* string = malloc(sizeof(string_t));
    string->next = NULL;
    string->prev = NULL;
    string->position = 0;
    string->len = 0;
    string->str[0] = '\0';
    string->hour[0] = '\0';
    return string;
}

void append_string(char c, string_t* string)
{
    char cpy[4096] = {0};
    int diff = string->len - string->position;
    strncpy(cpy, string->str, string->position);
    strncat(cpy, &c, 1);
    strncat(cpy, string->str + string->position, diff);
    string->len++;
    string->position++;
    strncpy(string->str, cpy, string->len);
}

void print_string(string_t* string)
{
    for (int i = 0; i < string->len; i++)
        dprintf(1, "%c", string->str[i]);
}

void copy_string(string_t* dest, string_t* src)
{
    dest->len = src->len;
    dest->position = src->position;
    for (int i = 0; i < src->len; i++)
        dest->str[i] = src->str[i];
}

char* merge_string(string_t* string)
{
    int i = 0;
    char* str = malloc(sizeof(char) * (string->len + 1));
    for (int i = 0; i < string->len; i++)
        str[i] = string->str[i];
    str[string->len] = '\0';
    return str;
}
