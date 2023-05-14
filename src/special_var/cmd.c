/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** cmd
*/

#include "mysh.h"

void postcmd(shell_t* shell)
{
    list_t *list_postcmd = parse_command(shell->postcmd, shell);
    shell->loop_postcmd = 1; handle_command(list_postcmd, shell);
}

void precmd(shell_t* shell)
{
    shell->loop_postcmd = 1;
    list_t *list_precmd = parse_command(shell->precmd, shell);
    shell->loop = 1; handle_command(list_precmd, shell);
}
