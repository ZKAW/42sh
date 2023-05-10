/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** manage
*/

#include "mysh.h"

int is_pid_alive(pid_t pid)
{
    if (kill(pid, 0) == -1)
        return 0;
    return 1;
}

void set_job_status(shell_t *shell, job_t *job, job_status_t status)
{
    int i = 0;

    for (; shell->jobs[i]; i++) {
        if (shell->jobs[i] == job) {
            shell->jobs[i]->status = status;
            job->status = status;
            return;
        }
    }
}
