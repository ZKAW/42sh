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

    if (!shell->job_control->jobs) {
        shell->job_control->jobs = malloc(sizeof(job_t *) * 2);
        shell->job_control->jobs[0] = job;
        shell->job_control->jobs[1] = NULL;
        return;
    }
    for (; shell->job_control->jobs[i]; i++);
    shell->job_control->jobs = realloc(shell->job_control->jobs,
                                sizeof(job_t *) * (i + 2));
    shell->job_control->jobs[i] = job;
    shell->job_control->jobs[i + 1] = NULL;
}

void remove_job(shell_t *shell, job_t *job)
{
    int i = 0;
    int j = 0;
    job_t **new_jobs = malloc(sizeof(job_t *) * (shell->job_control->job_nb));

    for (; shell->job_control->jobs[i]; i++) {
        if (shell->job_control->jobs[i] != job) {
            new_jobs[j] = shell->job_control->jobs[i];
            j++;
        }
    }
    new_jobs[j] = NULL;
    free(shell->job_control->jobs);
    shell->job_control->jobs = new_jobs;
    shell->job_control->job_nb--;
}

void set_job_status(shell_t *shell, job_t *job, job_status_t status)
{
    int i = 0;

    for (; shell->job_control->jobs[i]; i++) {
        if (shell->job_control->jobs[i] == job) {
            shell->job_control->jobs[i]->status = status;
            job->status = status;
            return;
        }
    }
}
