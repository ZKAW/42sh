/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** display
*/

#include "mysh.h"

/*
typedef enum job_status_e {
    RUNNING,
    SUSPENDED,
    TERMINATED
} job_status_t;
*/

static void display_job(job_t *job, int verbose)
{
    fflush(stdout);
    printf("[%d]  %c ", job->id, job->type == FG ? '+' : ' ');
    if (verbose) {
        printf("%d ", job->pgid);
    }
    if (job->status == RUNNING) {
        printf("Running                       ");
    } else if (job->status == SUSPENDED) {
        printf("Suspended                     ");
    } else {
        printf("Terminated                    ");
    }
    printf("%s\n", job->name);
}

void display_jobs(shell_t *shell, int verbose)
{
    int i = 0;

    for (; shell->jobs[i]; i++) {
        if (is_pid_alive(shell->jobs[i]->pgid) == 0) {
            shell->jobs[i]->status = TERMINATED;
        }
        display_job(shell->jobs[i], verbose);
        if (shell->jobs[i]->status == TERMINATED) {
            free(shell->jobs[i]);
            shell->jobs[i] = NULL;
            continue;
        }
    }
}
