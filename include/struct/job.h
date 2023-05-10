/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** jobs
*/

#ifndef JOBS_H_
    #define JOBS_H_

    #include <sys/types.h>

    #define IS_JOB_BG(job) (job && job->type == BG)

typedef enum job_status_e {
    RUNNING,
    SUSPENDED,
    TERMINATED
} job_status_t;

typedef enum job_type_e {
    FG,
    BG
} job_type_t;

typedef struct job_s {
    int id;
    char* name;
    pid_t pgid;
    job_status_t status;
    job_type_t type;
} job_t;

#endif /* !JOBS_H_ */
