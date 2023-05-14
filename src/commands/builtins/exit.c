/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** exit
*/

#include "mysh.h"

void builtin_exit(BUILTIN_PARAMS)
{
    char** cmd = command->argv;
    if (tablen(cmd) > 2) {
        throw_error("exit: Expression Syntax.\n", shell, 1);
        return;
    }
    if (tablen(cmd) == 2) {
        if (is_number(cmd[1])) {
            exit(atoi(cmd[1]));
        } else {
            throw_error("exit: Expression Syntax.\n", shell, 1);
            return;
        }
    }
    exit(0);
    shell->state = 0;
}
