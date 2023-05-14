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

static void init_aliases(shell_t* shell)
{
    shell->aliases = malloc(sizeof(alias_t));
    shell->aliases->alias = NULL;
    shell->aliases->command = NULL;
    shell->aliases->next = NULL;
}

static void init_paths(shell_t *shell)
{
    char *PATH = get_env_var(shell->envp, "PATH");
    if (PATH == NULL) {
        shell->paths = NULL;
        return;
    }
    shell->paths = tokenize_string(PATH, ":");
}

shell_t* init_shell(char** envp, char** av)
{
    shell_t* shell = malloc(sizeof(shell_t));
    shell->root = malloc(sizeof(char) * 500);
    shell->root = getcwd(shell->root, 500);
    shell->envp = envp_cpy(envp);
    shell->binary_name = av[0];
    shell->state = 0;
    shell->history.head = NULL;
    shell->history.tail = NULL;
    shell->history.current = NULL;
    shell->history.position = 0;
    shell->history.len = 0;
    shell->pgid = getpgrp();
    shell->pid = getpid();
    shell->shared_status = create_shm(EXIT_SUCCESS);
    shell->job_control = init_job_control();
    init_aliases(shell);
    init_vars(shell);
    init_paths(shell);
    return shell;
}
