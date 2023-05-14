/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** if
*/

#include "mysh.h"

static char *apply_variable(shell_t *shell, char* var)
{
    if (var[0] == '$') {
        char *res = get_local_var(shell, var + 1);
        if (res) return res;
    }
    return var;
}

static void exec_if_condition(cmd_t *cmd, shell_t *shell)
{
    if_t* statement = cmd->if_statement;
    if (statement->conditions[1] == NULL ||
        statement->conditions[2] == NULL) {
        if (atoi(statement->conditions[0])) {
            handle_command(parse_command(statement->cmd, shell), shell);
        }
        return;
    }
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

static void prompt_if_args(BUILTIN_PARAMS)
{
    char* line = "";
    ssize_t size = 0; size_t i = 0;
    cmd->if_statement->cmd = malloc(sizeof(char) * 1);
    cmd->if_statement->cmd[0] = '\0';
    while (1) {
        my_putstr("if? ", 1);
        size = my_getline(&line, shell);
        if (size == 1) continue;
        if (size == EOF) break;
        line[size - 1] = '\0';
        if (!strcmp(clean_str(line), "endif")) break;
        char *tmp = malloc(sizeof(char) *
                    (strlen(cmd->if_statement->cmd) + size + 2));
        strcpy(tmp, cmd->if_statement->cmd);
        strcat(tmp, line);
        strcat(tmp, ";");
        cmd->if_statement->cmd = tmp;
        i++;
    }
    handle_command(parse_command(cmd->if_statement->cmd, shell), shell);
}

void builtin_if(BUILTIN_PARAMS)
{
    if_t* statement = cmd->if_statement;

    if ((statement->cmd == NULL) || (is_whitespace(statement->cmd))) {
        prompt_if_args(cmd, shell);
        return;
    }

    exec_if_condition(cmd, shell);
}
