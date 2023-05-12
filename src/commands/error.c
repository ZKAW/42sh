/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** error
*/

#include "mysh.h"

int not_existing(char* path, shell_t* shell)
{
    if (access(path, F_OK) == 0)
        return 0;
    dprintf(2, "%s: Command not found.\n", path);
    shell->state = 1;
    set_status(shell, shell->state);
    return 1;
}

void handle_child_error(char** argv)
{
    if (errno == 8) {
        dprintf(2, "%s: Exec format error. Wrong Architecture.\n", argv[0]);
    }
    if (errno == 13) {
        dprintf(2, "%s: Permission denied.\n", argv[0]);
    }
    exit(1);
}

int handle_status(int state)
{
    int return_value = 0;

    if (WIFEXITED(state)) {
        return_value = WEXITSTATUS(state);
        return return_value;
    }
    if (WIFSIGNALED(state)) {
        if (WTERMSIG(state) == SIGSEGV)
            write(2, "Segmentation fault", 18);
        if (WTERMSIG(state) == SIGFPE)
            write(2, "Floating exception", 18);
        if (WCOREDUMP(state))
            write(2, " (core dumped)", 14);
        write(2, "\n", 1);
    }
    return state;
}
