/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** cwd
*/

#include "mysh.h"

void update_cwd(shell_t *shell)
{
    char *cwd = malloc(sizeof(char) * 500);
    cwd = getcwd(cwd, 500);
    set_var(shell, "cwd", cwd);
    set_status(shell, 0);
}
