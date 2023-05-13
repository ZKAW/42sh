/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** separators.c
*/

#include "mysh.h"

void close_cmd(cmd_t* cmd);
cmd_t* append_command(list_t* array);
list_t* append_list(list_t* array);

char* parse_pipe(char* cmd_str, list_t** command_array, shell_t* shell)
{
    (void)shell;
    if ((*command_array)->cmd == NULL)
        append_command(*command_array);
    (*command_array)->cmd->output_type = PIPE;
    append_command(*command_array);
    (*command_array)->cmd->input_type = PIPE;
    return cmd_str;
}

char* parse_semicolon(char* cmd_str, list_t** command_array, shell_t* shell)
{
    (void)shell;
    close_cmd((*command_array)->cmd);
    *command_array = append_list(*command_array);
    return cmd_str;
}

char* parse_quotes(char* cmd_str, list_t** command_array, shell_t* shell)
{
    char buffer[4096] = {0};
    cmd_t* cmd = (*command_array)->cmd;
    char quote = *(cmd_str - 1);
    while (!(*cmd_str == quote && *(cmd_str - 1) != '|') && *cmd_str != '\0') {
        strncat(buffer, cmd_str, 1);
        cmd_str++;
    }
    cmd_str++;
    add_arg(*command_array, strdup(buffer), QUOTTED);
    return cmd_str;
}
