/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** ll_parser.c
*/

#include "mysh.h"
#include "parsing.h"

char *skip_whitespace(char *str);

char* parse_token(char* cmd_str, cmd_t* cmd)
{
    int is_token = 0;
    for (int i = 0; tokens[i]; i++) {
        if (strncmp(cmd_str, tokens[i], strlen(tokens[i])) == 0) {
            is_token = 1;
            cmd_str = skip_whitespace(cmd_str + strlen(tokens[i]));
            cmd_str = parsers[i](cmd_str, cmd);
            break;
        }
    }
    if (!is_token)
        cmd_str = parse_default_token(cmd_str, cmd);
    return cmd_str;
}

void parse_command(char *cmd_str, cmd_t *cmd)
{
    *cmd = (cmd_t){0};
    while (*cmd_str && cmd->argc < MAX_ARGS) {
        cmd_str = skip_whitespace(cmd_str);
        if (*cmd_str == '\0')
            break;
        cmd_str = parse_token(cmd_str, cmd);
    }
    if (cmd->argc == 0)
        error("Empty command");
    cmd->argv[cmd->argc] = NULL;
    cmd->path = cmd->argv[0];
}
