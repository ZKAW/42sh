/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** parenthesis.c
*/

#include "mysh.h"

char* parse_parenthesis(char* cmd_str, list_t** command_array, shell_t* shell)
{
    (void)shell;
    append_command(*command_array);
    return cmd_str;
}

char* parse_or(char* cmd_str, list_t** command_array, shell_t* shell UNUSED)
{
    (void)shell;
    close_cmd((*command_array)->cmd);
    *command_array = append_list(*command_array);
    append_command(*command_array);
    (*command_array)->condition = OR;
    return cmd_str;
}

char* parse_and(char* cmd_str, list_t** command_array, shell_t* shell UNUSED)
{
    (void)shell;
    close_cmd((*command_array)->cmd);
    *command_array = append_list(*command_array);
    append_command(*command_array);
    (*command_array)->condition = AND;
    return cmd_str;
}
