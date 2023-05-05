/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** ll_parser.c
*/

#include "mysh.h"
#include "parsing.h"

char *skip_whitespace(char *str);

char* parse_default_token(char* cmd_str, list_t** command_array)
{
    char arg[256];
    cmd_t* cmd = (*command_array)->cmd;
    cmd_str = copy_until(arg, cmd_str, ";><| \t\n");
    cmd->argv[cmd->argc] = strdup(arg);
    cmd->argc++;
    return cmd_str;
}

char* parse_token(char* cmd_str, list_t** array)
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

list_t* append_list(list_t* array)
{
    list_t* new_list = malloc(sizeof(list_t));
    *new_list = (list_t){0};
    if (array)
        array->prev = new_list;
    new_list->next = array;
    return new_list;
}

list_t* parse_command(char *cmd_str)
{
    list_t* command_array = append_list(NULL);
    append_command(command_array);
    while (*cmd_str && command_array->cmd->argc < MAX_ARGS) {
        cmd_str = skip_whitespace(cmd_str);
        if (*cmd_str == '\0')
            break;
        cmd_str = parse_token(cmd_str, &command_array);
    }
    if (command_array->cmd->argc == 0)
        error("Empty command");
    close_cmd(command_array->cmd);
    return command_array;
}
