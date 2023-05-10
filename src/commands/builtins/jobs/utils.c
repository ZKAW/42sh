/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** utils
*/

#include "mysh.h"

int is_pid_alive(pid_t pid)
{
    if (kill(pid, 0) == -1)
        return 0;
    return 1;
}
