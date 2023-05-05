/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** ll_parser.c
*/

#include "mysh.h"
#include "parsing.h"

char *skip_whitespace(char *str);

char* parse_token(char* cmd_str, list_t* array)
{
    int is_token = 0;
    for (int i = 0; tokens[i]; i++) {
        if (strncmp(cmd_str, tokens[i], strlen(tokens[i])) == 0) {
            is_token = 1;
            cmd_str = skip_whitespace(cmd_str + strlen(tokens[i]));
            cmd_str = parsers[i](cmd_str, array);
            break;
        }
    }
    if (!is_token)
        cmd_str = parse_default_token(cmd_str, array);
    return cmd_str;
}

cmd_t* append_command(list_t* array)
{
    cmd_t* new_cmd = malloc(sizeof(cmd_t));
    if (array->cmd) {
        array->cmd->argv[array->cmd->argc] = NULL;
        array->cmd->path = array->cmd->argv[0];
        array->cmd->prev = new_cmd;
    }
    *new_cmd = (cmd_t){0};
    new_cmd->next = array->cmd;
    array->cmd = new_cmd;
    return new_cmd;
}

void parse_command(char *cmd_str, list_t *command_array)
{
    append_command(command_array);
    while (*cmd_str && command_array->cmd->argc < MAX_ARGS) {
        cmd_str = skip_whitespace(cmd_str);
        if (*cmd_str == '\0')
            break;
        cmd_str = parse_token(cmd_str, command_array);
    }
    if (command_array->cmd->argc == 0)
        error("Empty command");
    command_array->cmd->argv[command_array->cmd->argc] = NULL;
    command_array->cmd->path = command_array->cmd->argv[0];
}
