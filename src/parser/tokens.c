/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** tokens.c
*/

#include "mysh.h"

cmd_t* append_command(list_t* array);

char* parse_file_name(char** cmd_str)
{
    char out_file[256];
    *cmd_str = copy_until(out_file, *cmd_str, "; \t\n");
    return strdup(out_file);
}

char* parse_double_output(char* cmd_str, list_t* command_array)
{
    cmd_t* cmd = command_array->cmd;
    if (*cmd_str == '\0')
        error("Missing name for redirect.");
    cmd->output = parse_file_name(&cmd_str);
    cmd->append = O_APPEND;
    cmd->output_type = FILE_PATH;
    return cmd_str;
}

char* parse_single_output(char* cmd_str, list_t* command_array)
{
    cmd_t* cmd = command_array->cmd;
    if (*cmd_str == '\0')
        error("Missing name for redirect.");
    cmd->output = parse_file_name(&cmd_str);
    cmd->append = O_TRUNC;
    cmd->output_type = FILE_PATH;
    return cmd_str;
}

char* parse_single_input(char* cmd_str, list_t* command_array)
{
    cmd_t* cmd = command_array->cmd;
    if (*cmd_str == '\0')
        error("Missing name for redirect.");
    cmd->input = parse_file_name(&cmd_str);
    cmd->input_type = FILE_PATH;
    return cmd_str;
}

char* parse_double_input(char* cmd_str, list_t* command_array)
{
    cmd_t* cmd = command_array->cmd;
    if (*cmd_str == '\0')
        error("Missing name for redirect.");
    cmd->input = parse_file_name(&cmd_str);
    cmd->input_type = STD;
    return cmd_str;
}

char* parse_default_token(char* cmd_str, list_t* command_array)
{
    char arg[256];
    cmd_t* cmd = command_array->cmd;
    cmd_str = copy_until(arg, cmd_str, ";><| \t\n");
    cmd->argv[cmd->argc] = strdup(arg);
    cmd->argc++;
    return cmd_str;
}

char* parse_pipe(char* cmd_str, list_t* command_array)
{
    command_array->cmd->output_type = PIPE;
    append_command(command_array);
    command_array->cmd->input_type = PIPE;
    return cmd_str;
}