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
    SHARED_STATUS = shell->state;
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

int handle_status(shell_t* shell, cmd_t* cmd, int state)
{
    int return_value = 0;

    if (WIFEXITED(state)) {
        return_value = WEXITSTATUS(state);
        if (return_value == 0 && cmd->input_type == PIPE)
            return 0;
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
