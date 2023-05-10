/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** manage
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

void remove_job(shell_t *shell, job_t *job)
{
    int i = 0;
    int j = 0;
    job_t **new_jobs = malloc(sizeof(job_t *) * (shell->job_nb));

    for (; shell->jobs[i]; i++) {
        if (shell->jobs[i] != job) {
            new_jobs[j] = shell->jobs[i];
            j++;
        }
    }
    new_jobs[j] = NULL;
    free(shell->jobs);
    shell->jobs = new_jobs;
    shell->job_nb--;
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
