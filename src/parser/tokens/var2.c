/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** var2.c
*/

#include "mysh.h"

char* get_next_token(char* cmd_str, char* delims);

char* parse_var_name(char** cmd_str)
{
    char* var_name = NULL;
    if (**cmd_str == '{') {
        (*cmd_str)++;
        var_name = get_next_token(*cmd_str, "}");
        (*cmd_str) += strlen(var_name) + 1;
    } else {
        var_name = get_next_token(*cmd_str, " \t\n;|&<>");
        (*cmd_str) += strlen(var_name);
    }
    return var_name;
}
