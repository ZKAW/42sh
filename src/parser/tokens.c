/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** tokens.c
*/

#include "mysh.h"

char* parse_file_name(char** cmd_str)
{
    char out_file[256];
    *cmd_str = copy_until(out_file, *cmd_str, " \t\n");
    return strdup(out_file);
}

char* parse_double_redirect(char* cmd_str, cmd_t* cmd)
{
    if (*cmd_str == '\0')
        error("Missing name for redirect.");
    cmd->output = parse_file_name(&cmd_str);
    cmd->append = O_APPEND;
    cmd->output_type = FILE_PATH;
    return cmd_str;
}

char* parse_single_redirect(char* cmd_str, cmd_t* cmd)
{
    if (*cmd_str == '\0')
        error("Missing name for redirect.");
    cmd->output = parse_file_name(&cmd_str);
    cmd->append = O_TRUNC;
    cmd->output_type = FILE_PATH;
    return cmd_str;
}

char* parse_input_redirect(char* cmd_str, cmd_t* cmd)
{
    if (*cmd_str == '\0')
        error("Missing name for redirect.");
    cmd->input = parse_file_name(&cmd_str);
    cmd->input_type = FILE_PATH;
    return cmd_str;
}

char* parse_default_token(char* cmd_str, cmd_t* cmd)
{
    char arg[256];
    cmd_str = copy_until(arg, cmd_str, "><| \t\n");
    cmd->argv[cmd->argc] = strdup(arg);
    cmd->argc++;
    return cmd_str;
}
