/*
** EPITECH PROJECT, 2022
** mini-shell1
** File description:
** env.c
*/

#include "mysh.h"

void builtin_env(char** cmd UNUSED, shell_t* shell)
{
    print_array(shell->envp);
}
