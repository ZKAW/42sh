/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** ll_parser.c
*/

#include "mysh.h"

int is_char_whitespace(char c);
char *skip_whitespace(char *str);
char *skip_non_whitespace(char *str);
char *copy_until(char *dst, char *src, char *delim);
char* parse_file_name(char** cmd_str);
void error(char *msg);

char* parse_double_redirect(char* cmd_str, cmd_t* cmd);
char* parse_single_redirect(char* cmd_str, cmd_t* cmd);
char* parse_input_redirect(char* cmd_str, cmd_t* cmd);
char* parse_default_token(char* cmd_str, cmd_t* cmd);

char* parse_token(char* cmd_str, cmd_t* cmd, int* is_token)
{
    char* tokens[100] = {">", ">>", "<", NULL};
    char* (*parsers[3])(char*, cmd_t*) = {
        parse_single_redirect, parse_double_redirect, parse_input_redirect
    };
    *is_token = 0;
    for (int i = 0; tokens[i]; i++) {
        if (strncmp(cmd_str, tokens[i], strlen(tokens[i])) == 0) {
            *is_token = 1;
            cmd_str = skip_whitespace(cmd_str + strlen(tokens[i]));
            cmd_str = parsers[i](cmd_str, cmd);
            break;
        }
    }
    return cmd_str;
}

void parse_command(char *cmd_str, cmd_t *cmd)
{
    *cmd = (cmd_t){0};
    int is_token;
    while (*cmd_str && cmd->argc < MAX_ARGS) {
        cmd_str = skip_whitespace(cmd_str);
        if (*cmd_str == '\0')
            break;
        cmd_str = parse_token(cmd_str, cmd, &is_token);
        if (!is_token)
            cmd_str = parse_default_token(cmd_str, cmd);
    }
    if (cmd->argc == 0)
        error("Empty command");
    cmd->argv[cmd->argc] = NULL;
    cmd->path = cmd->argv[0];
}
