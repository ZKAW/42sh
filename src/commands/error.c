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
    write(2, path, strlen(path));
    write(2, ": Command not found.\n", 21);
    shell->state = 1;
    return 1;
}

void handle_child_error(char** argv)
{
    if (errno == 8) {
        write(2, argv[0], strlen(argv[0]));
        write(2, ": Exec format error. Wrong Architecture.\n", 41);
    }
    if (errno == 13) {
        write(2, argv[0], strlen(argv[0]));
        write(2, ": Permission denied.\n", 21);
    }
    exit(1);
}

void handle_status(shell_t* shell, cmd_t* cmd)
{
    int return_value = 0;

    if (WIFEXITED(shell->state)) {
        return_value = WEXITSTATUS(shell->state);
        if (return_value == 0 && cmd->input_type == PIPE)
            return;
        shell->state = return_value;
        return;
    }
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
