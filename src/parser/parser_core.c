/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** ll_parser.c
*/

#include "../../include/mysh.h"

int is_char_whitespace(char c);
char *skip_whitespace(char *str);
char *skip_non_whitespace(char *str);
char *copy_until(char *dst, char *src, char *delim);
char* parse_file_name(char** cmd_str);
void error(char *msg);

void parse_command(char *cmd_str, cmd_t *cmd)
{
    *cmd = (cmd_t){0};
    int argc = 0;
    while (*cmd_str && argc < MAX_ARGS) {
        cmd_str = skip_whitespace(cmd_str);
        if (*cmd_str == '\0')
            break;
        if (*cmd_str == '>' && *(cmd_str + 1) == '>') {
            cmd_str = skip_whitespace(cmd_str + 2);
            if (*cmd_str == '\0')
                error("Missing name for redirect.");
            cmd->output = parse_file_name(&cmd_str);
            cmd->append = O_APPEND;
            cmd->output_type = FILE_PATH;
        } else if (*cmd_str == '>') {
            cmd_str = skip_whitespace(cmd_str + 1);
            if (*cmd_str == '\0')
                error("Missing name for redirect.");
            cmd->output = parse_file_name(&cmd_str);
            cmd->append = O_TRUNC;
            cmd->output_type = FILE_PATH;
        } else if (*cmd_str == '<') {
            cmd_str = skip_whitespace(cmd_str + 1);
            if (*cmd_str == '\0')
                error("Missing name for redirect.");
            cmd->input = parse_file_name(&cmd_str);
            cmd->input_type = FILE_PATH;    
        } else {
            char arg[256];
            cmd_str = copy_until(arg, cmd_str, "><| \t\n");
            cmd->argv[argc] = strdup(arg);
            argc++;
        }
    }
    if (argc == 0)
        error("Empty command");
    cmd->argv[argc] = NULL;
    cmd->path = cmd->argv[0];
}