/*
** EPITECH PROJECT, 2022
** mini-shell2
** File description:
** commands.c
*/

#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include "mysh.h"


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

char* get_actual_command(shell_t* shell)
{
    char command[4096] = {0};
    string_t* string = get_string(NULL);
    if (string == NULL)
        return NULL;
    for (int i = 0; i < string->len; i++)
        command[i] = string->str[i];
    return strdup(command);
}

int end_of_input(shell_t* shell)
{
    string_t* string = get_string(NULL);
    dprintf(1, "%c", '\n');
    completion(get_actual_command(shell), shell->envp);
    my_putstr(get_prompt_prefix(), 1);
    print_string(string);
    return 1;
}

int handle_commands(char c, shell_t* shell)
{
    string_t* string = shell->string;
    if (handle_backspace(c, string))
        return 1;
    if (c == '\003') {
        if (string->len != 0) {
            dprintf(1, "^C\n");
            string->len = 0;
            string->position = 0;
            string->str[0] = '\0';
        }
        return 1;
    }
    if (c == '\004')
        return end_of_input(shell);
    if (c == '\033') {
        if (handle_arrows(shell))
            return 1;
    }
    return 0;
}
