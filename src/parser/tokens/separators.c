/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** separators.c
*/

#include "mysh.h"

cmd_t* append_command(list_t* array);


void close_cmd(cmd_t* cmd)
{
    cmd->argv[cmd->argc] = NULL;
    cmd->path = cmd->argv[0];
}

cmd_t* append_command(list_t* array)
{
    cmd_t* new_cmd = malloc(sizeof(cmd_t));
    if (array->cmd) {
        close_cmd(array->cmd);
        array->cmd->prev = new_cmd;
    }
    *new_cmd = (cmd_t){0};
    new_cmd->next = array->cmd;
    array->cmd = new_cmd;
    return new_cmd;
}

list_t* append_list(list_t* array)
{
    list_t* new_list = malloc(sizeof(list_t));
    *new_list = (list_t){0};
    if (array)
        array->prev = new_list;
    new_list->next = array;
    return new_list;
}

char* parse_pipe(char* cmd_str, list_t** command_array, shell_t* shell)
{
    (void)shell;
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
    append_command(*command_array);
    return cmd_str;
}
