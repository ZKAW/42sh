/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** if_statement.c
*/

#include "mysh.h"
#include "parsing.h"

char *skip_whitespace(char *str);

// typedef struct if_s {
//     char **values;
//     char *cmd;
// } if_t;

/*
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
    while (*cmd_str && strncmp(cmd_str, "end", 3)) {
        strncat(buffer, cmd_str++, 1);
    }
    strncat(buffer, cmd_str, 3);
    cmd_str += 3;
    add_arg(*command_array, strdup("foreach"), SIMPLE);
    (*command_array)->cmd->foreach = fill_foreach(buffer);
    return cmd_str;
}
*/

/*
if ( 10 == 10 ) then ; echo "x is equal to 10" ; endif
*/

if_t* fill_if(char* if_statement)
{
    char buffer[4096] = {0};
    if_t* if_struct = malloc(sizeof(if_t));
    if_statement = skip_whitespace(if_statement);
    if_statement++;
    if_statement = copy_until(buffer, if_statement, ")");
    if_statement++;
    if_struct->values = tokenize_string(buffer, " \t\n");
    return if_struct;
}

char* parse_if(char* cmd_str, list_t** command_array, shell_t* shell)
{
    if_t* if_struct;
    char buffer[4096] = {0};
    while (*cmd_str && strncmp(cmd_str, "endif", 5)) {
        strncat(buffer, cmd_str++, 1);
    }
    strncat(buffer, cmd_str, 5);
    cmd_str += 5;
    add_arg(*command_array, strdup("if"), SIMPLE);
    (*command_array)->cmd->if_statement = fill_if(buffer);
    return cmd_str;
}
