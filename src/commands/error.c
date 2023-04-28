/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** error
*/

#include "mysh.h"

int not_existing(char* path, shell_t* shell)
{
    write(2, path, strlen(path));
    write(2, ": Command not found.\n", 21);
    shell->state = 1;
    return 1;
}

void handle_error(shell_t* shell)
{
    if (WIFSIGNALED(shell->state)) {
        if (WTERMSIG(shell->state) == SIGSEGV)
            write(2, "Segmentation fault", 18);
        if (WTERMSIG(shell->state) == SIGFPE)
            write(2, "Floating exception", 18);
        if (WCOREDUMP(shell->state))
            write(2, " (core dumped)", 14);
        write(2, "\n", 1);
    }
    if (shell->state == 256 || shell->state == 15)
        shell->state = 1;
}