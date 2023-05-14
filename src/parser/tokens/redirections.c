/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** redirections.c
*/

#include "mysh.h"

char* parse_file_name(char** cmd_str)
{
    char out_file[256];
    *cmd_str = copy_until(out_file, *cmd_str, ";><| \t\n");
    return strdup(out_file);
}

char* parse_double_output(char* cmd_str, list_t** command_array, shell_t* shell)
{
    cmd_t* cmd = (*command_array)->cmd;
    cmd = cmd ? cmd : append_command(*command_array);
    (void)shell;
    if (*cmd_str == '\0')
        error("Missing name for redirect.");
    cmd->output = parse_file_name(&cmd_str);
    cmd->append = O_APPEND;
    cmd->output_type = FILE_PATH;
    return cmd_str;
}

char* parse_single_output(char* cmd_str, list_t** command_array, shell_t* shell)
{
    cmd_t* cmd = (*command_array)->cmd;
    cmd = cmd ? cmd : append_command(*command_array);
    (void)shell;
    if (*cmd_str == '\0')
        error("Missing name for redirect.");
    cmd->output = parse_file_name(&cmd_str);
    cmd->append = O_TRUNC;
    cmd->output_type = FILE_PATH;
    return cmd_str;
}

char* parse_single_input(char* cmd_str, list_t** command_array, shell_t* shell)
{
    cmd_t* cmd = (*command_array)->cmd;
    cmd = cmd ? cmd : append_command(*command_array);
    (void)shell;
    if (*cmd_str == '\0')
        error("Missing name for redirect.");
    cmd->input = parse_file_name(&cmd_str);
    cmd->input_type = FILE_PATH;
    return cmd_str;
}

char* parse_double_input(char* cmd_str, list_t** command_array, shell_t* shell)
{
    cmd_t* cmd = (*command_array)->cmd;
    cmd = cmd ? cmd : append_command(*command_array);
    (void)shell;
    if (*cmd_str == '\0')
        error("Missing name for redirect.");
    cmd->input = parse_file_name(&cmd_str);
    cmd->input_type = STD;
    return cmd_str;
}
