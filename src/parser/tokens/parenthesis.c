/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** parenthesis.c
*/

#include "mysh.h"

void dump_list(list_t* list);

char* parse_parenthesis(char* cmd_str, list_t** command_array, shell_t* shell)
{
    (void)shell;
    char buffer[4096] = {0};
    cmd_t* cmd = (*command_array)->cmd ?
    (*command_array)->cmd : append_command(*command_array);
    cmd_str = copy_until(buffer, cmd_str, ")");
    cmd->subshell = parse_command(buffer, shell);
    cmd_str++;
    close_cmd(cmd);
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
