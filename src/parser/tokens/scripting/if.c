/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** if_statement.c
*/

#include "mysh.h"
#include "parsing.h"

char *skip_whitespace(char *str);

if_t* fill_if(char* if_statement, shell_t *shell)
{
    char buffer[4096] = {0};
    char cmd[4096] = {0};
    char parentheses[4096] = {0};
    if_t* if_struct = malloc(sizeof(if_t));
    if_statement = copy_until(buffer, if_statement, "(");
    if_statement++;
    if_statement = copy_until(parentheses, if_statement, ")");
    while (*if_statement && strncmp(if_statement, "then", 4)) if_statement++;
    if (*if_statement != '\0') {
        if_statement += 4;
    } else {
        throw_error("if: Empty if.\n", shell, 1); return NULL;
    }
    if_statement = copy_until(buffer, if_statement, ";");
    if (*if_statement != '\0') if_statement++;
    while (*if_statement && strncmp(if_statement, "endif", 5))
        strncat(cmd, if_statement++, 1);
    if_struct->cmd = strdup(cmd);
    if_struct->conditions = tokenize_string(parentheses, " \t\n");
    return if_struct;
}

char* parse_if(char* cmd_str, list_t** command_array, shell_t* shell)
{
    if_t* if_struct;
    char buffer[4096] = {0};
    while (*cmd_str && strncmp(cmd_str, "endif", 5)) {
        strncat(buffer, cmd_str++, 1);
    }
    if (*cmd_str != '\0') {
        strncat(buffer, cmd_str, 5);
        cmd_str += 5;
    }
    add_arg(*command_array, strdup("if"), SIMPLE);
    (*command_array)->cmd->if_statement = fill_if(buffer, shell);
    return cmd_str;
}
