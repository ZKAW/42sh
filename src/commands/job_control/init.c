/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** job_control
*/

#include "mysh.h"

void add_job(shell_t *shell, job_t *job)
{
    int i = 0;

    if (!shell->jobs) {
        shell->jobs = malloc(sizeof(job_t *) * 2);
        shell->jobs[0] = job;
        shell->jobs[1] = NULL;
        return;
    }
    for (; shell->jobs[i]; i++);
    shell->jobs = realloc(shell->jobs, sizeof(job_t *) * (i + 2));
    shell->jobs[i] = job;
    shell->jobs[i + 1] = NULL;
}

job_t *init_job(shell_t *shell, char *name)
{
    job_t *job = malloc(sizeof(job_t));

    job->name = name;
    job->pgid = -1;
    job->status = RUNNING;
    shell->job_nb++;
    job->id = shell->job_nb;
    add_job(shell, job);

    return job;
}
