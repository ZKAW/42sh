/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** jobs
*/

#ifndef JOBS_H_
    #define JOBS_H_

    #include <sys/types.h>

typedef enum job_status_e {
    RUNNING,
    SUSPENDED,
    TERMINATED
} job_status_t;

typedef struct job_s {
    int id;
    char* name;
    pid_t pgid;
    job_status_t status;
} job_t;

#endif /* !JOBS_H_ */
