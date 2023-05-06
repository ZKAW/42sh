/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** exit
*/

#include "mysh.h"

void builtin_exit(char** cmd, shell_t* shell)
{
    if (tablen(cmd) > 2) {
        dprintf(2, "exit: Expression Syntax.\n");
        shell->state = 1;
        return;
    }
    if (tablen(cmd) == 2) {
        if (is_number(cmd[1])) {
            exit(atoi(cmd[1]));
        } else {
            dprintf(2, "exit: Expression Syntax.\n");
            shell->state = 1;
            return;
        }
    }
    exit(0);
    shell->state = 0;
}
