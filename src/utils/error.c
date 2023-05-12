/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** error
*/

#include "mysh.h"

void error(char *msg)
{
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

void throw_error(char* const strerror, shell_t* shell, int ernum)
{
    dprintf(2, "%s", strerror);
    shell->state = ernum;
    set_status(shell, ernum);
}
