/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** shell
*/

#include "mysh.h"

static job_control_t* init_job_control(void)
{
    job_control_t* job_control = malloc(sizeof(job_control_t));

    job_control->job_nb = 0;
    job_control->jobs = NULL;
    job_control->prev_job = NULL;
    job_control->current_job = NULL;
    return job_control;
}

shell_t* init_shell(char** envp)
{
    shell_t* shell = malloc(sizeof(shell_t));
    shell->root = malloc(sizeof(char) * 500);
    shell->root = getcwd(shell->root, 500);
    shell->envp = envp_cpy(envp);
    shell->last_path = malloc(sizeof (char) * 500);
    shell->state = 0;
    shell->history.head = NULL;
    shell->history.tail = NULL;
    shell->history.current = NULL;
    shell->history.position = 0;
    shell->history.len = 0;
    shell->pgid = getpgrp();
    shell->shared_status = create_shm(EXIT_SUCCESS);
    shell->job_control = init_job_control();
    shell->aliases = malloc(sizeof(alias_t));
    shell->aliases->alias = NULL;
    shell->aliases->command = NULL;
    shell->aliases->next = NULL;
    init_vars(shell);
    return shell;
}
