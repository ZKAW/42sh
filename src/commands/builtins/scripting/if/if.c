/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** if
*/

#include "mysh.h"

static char *apply_variable(shell_t *shell, char* var)
{
    if (var[0] == '$')
        return get_local_var(shell, var + 1);
    return var;
}

void builtin_if(BUILTIN_PARAMS)
{
    if_t* statement = cmd->if_statement;

    char *left_op = apply_variable(shell, statement->conditions[0]);
    char *op = cmd->if_statement->conditions[1];
    char *right_op = apply_variable(shell, statement->conditions[2]);

    for (int i = 0; if_conditions[i].op; i++) {
        if (!strcmp(if_conditions[i].op, op)) {
            statement->is_true = if_conditions[i].func(left_op, right_op);
            break;
        }
    }
    if (statement->is_true)
        handle_command(parse_command(statement->cmd, shell), shell);
}
