/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** jobs
*/

#include "mysh.h"

static int raise_jobs_errors(char **cmd, int cmd_len)
{
    if (cmd_len > 2) {
        fprintf(stderr, "jobs: Too many arguments.\n");
        return 1;
    }
    if (cmd_len == 2 && strcmp(cmd[1], "-l") != 0) {
        dprintf(2, "Usage: jobs [ -l ].\n");
        return 1;
    }
    return 0;
}

void builtin_jobs(BUILTIN_PARAMS)
{
    int cmd_len = tablen(cmd);

    if (raise_jobs_errors(cmd, cmd_len)) {
        shell->state = 1;
        SHARED_STATUS = shell->state;
        return;
    }

    display_jobs(shell, cmd_len == 1 ? 0 : 1);
}
