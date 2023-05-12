/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** handlers.c
*/

#include "mysh.h"

string_t* get_string(string_t* string);

void sigchld_handler(int signo)
{
    (void)signo;
}

void sigint_handler(int sig)
{
    string_t* string = get_string(NULL);
    (void)sig;
    if (string->len != 0) {
        write(STDOUT_FILENO, "^C", 2);
        string->len = 0;
        string->position = 0;
        string->str[0] = '\0';
    }
    write(STDOUT_FILENO, "\n", 1);
    my_putstr(get_prompt_prefix(), 1);
}

void sigtstp_handler(int sig)
{
    string_t* string = get_string(NULL);
    (void)string;
    (void)sig;
}
