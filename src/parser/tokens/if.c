/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** foreach.c
*/

#include "mysh.h"
#include "parsing.h"

char *skip_whitespace(char *str);

// foreach_t* fill_foreach(char* foreach)
// {
//     char buffer[4096] = {0};
//     foreach_t* foreach_struct = malloc(sizeof(foreach_t));
//     foreach = copy_until(foreach_struct->var_name, foreach, " \t\n");
//     foreach = skip_whitespace(foreach);
//     foreach++;
//     foreach = copy_until(buffer, foreach, ")");
//     foreach++;
//     foreach_struct->values = tokenize_string(buffer, " \t\n");
//     return foreach_struct;
// }

// char* parse_foreach(char* cmd_str, list_t** command_array, shell_t* shell)
// {
//     foreach_t* foreach;
//     char buffer[4096] = {0};
//     while (*cmd_str && strncmp(cmd_str, "end", 3)) {
//         strncat(buffer, cmd_str++, 1);
//     }
//     strncat(buffer, cmd_str, 3);
//     cmd_str += 3;
//     add_arg(*command_array, strdup("foreach"), SIMPLE);
//     (*command_array)->cmd->foreach = fill_foreach(buffer);
//     return cmd_str;
// }

// typedef struct if_s {
//     char *condition;
//     char *cmd;
//     char *else_cmd;
// } if_t;

/*
while (*cmd_str && strncmp(cmd_str, "end", 3)) {
    strncat(buffer, cmd_str++, 1);
}
strncat(buffer, cmd_str, 3);
cmd_str += 3;
add_arg(*command_array, strdup("if"), SIMPLE);
condition = copy_until(buffer, condition, "then");
cmd_str = skip_whitespace(cmd_str);
cmd = copy_until(buffer, cmd_str, "else");
cmd_str = skip_whitespace(cmd_str);
else_cmd = copy_until(buffer, cmd_str, "end");
(*command_array)->cmd->if_s = malloc(sizeof(if_t));
(*command_array)->cmd->if_s->condition = strdup(condition);
(*command_array)->cmd->if_s->cmd = strdup(cmd);
(*command_array)->cmd->if_s->else_cmd = strdup(else_cmd);
return cmd_str;
}
*/

// if statement exemple:
// if ( $x == 10 ) then ; echo "x is equal to 10" ; endif
if_t *fill_if(char *if_str)
{
    char buffer[4096] = {0};
    if_t *if_struct = malloc(sizeof(if_t));
    if_str = copy_until(if_struct->condition, if_str, "then");
    if_str = skip_whitespace(if_str);
    if_str++;
    if_str = copy_until(buffer, if_str, "else");
    if_str++;
    if_struct->cmd = strdup(buffer);
    if_str = skip_whitespace(if_str);
    if_str = copy_until(buffer, if_str, "endif");
    if_struct->else_cmd = strdup(buffer);
    return if_struct;
}

char *parse_if(char *cmd_str, list_t **command_array, shell_t *shell)
{
    char buffer[4096] = {0};
    char *condition = NULL;
    char *cmd = NULL;
    char *else_cmd = NULL;
    while (*cmd_str && strncmp(cmd_str, "endif", 5)) {
        strncat(buffer, cmd_str++, 1);
    }
    strncat(buffer, cmd_str, 5);
    cmd_str += 5;
    add_arg(*command_array, strdup("if"), SIMPLE);
    (*command_array)->cmd->if_statement = fill_if(buffer);
    return cmd_str;
}
