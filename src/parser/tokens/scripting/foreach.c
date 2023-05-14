/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** foreach.c
*/

#include "mysh.h"
#include "parsing.h"

char *skip_whitespace(char *str);

foreach_t* fill_foreach(char* foreach)
{
    char buffer[4096] = {0};
    foreach_t* foreach_struct = malloc(sizeof(foreach_t));
    foreach = copy_until(foreach_struct->var_name, foreach, " \t\n");
    foreach = skip_whitespace(foreach);
    foreach++;
    foreach = copy_until(buffer, foreach, ")");
    foreach++;
    foreach_struct->values = tokenize_string(buffer, " \t\n");
    return foreach_struct;
}

char* parse_foreach(char* cmd_str, list_t** command_array, shell_t* shell)
{
    foreach_t* foreach;
    char buffer[4096] = {0};
    while (*cmd_str != '\0' && strncmp(cmd_str, "end", 3)) {
        strncat(buffer, cmd_str++, 1);
    }
    if (*cmd_str != '\0') {
        strncat(buffer, cmd_str, 3);
        cmd_str += 3;
    }
    add_arg(*command_array, strdup("foreach"), SIMPLE);
    (*command_array)->cmd->foreach = fill_foreach(buffer);
    return cmd_str;
}
