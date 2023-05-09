/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** getter.c
*/

#include "mysh.h"

string_t* get_string(string_t* string)
{
    static string_t* saved_string = NULL;
    if (string != NULL) saved_string = string;
    return (saved_string);
}

shell_t* get_shell(shell_t* shell)
{
    static shell_t* saved_shell = NULL;
    if (shell != NULL) saved_shell = shell;
    return (saved_shell);
}
