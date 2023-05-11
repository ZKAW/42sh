/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** job_control
*/

#include "mysh.h"

job_t *init_job(shell_t *shell, char *name, job_type_t type)
{
    job_t *job = malloc(sizeof(job_t));

    job->name = name;
    job->pgid = -1;
    job->status = RUNNING;
    job->type = type;
    shell->job_control->job_nb++;
    job->id = shell->job_control->job_nb;
    add_job(shell, job);

    return job;
}
