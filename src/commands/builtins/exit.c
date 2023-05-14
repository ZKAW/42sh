/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** exit
*/

#include "mysh.h"

void builtin_exit(BUILTIN_PARAMS)
{
    if (tablen(cmd->argv) > 2) {
        throw_error("exit: Expression Syntax.\n", shell, BUILTIN_ERROR);
        return;
    }
    if (tablen(cmd->argv) == 2) {
        if (is_number(cmd->argv[1])) {
            exit(atoi(cmd->argv[1]));
        } else {
            throw_error("exit: Expression Syntax.\n", shell, BUILTIN_ERROR);
            return;
        }
    }
    exit(0);
}
