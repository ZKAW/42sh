/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** exec
*/

#include "mysh.h"

void teach_child(char* path, char** cmd, shell_t* shell)
{
    if (execve(path, cmd, shell->envp) == -1) {
        handle_child_error(cmd);
    }
}

char *get_local_var(shell_t *shell, char *key)
{
    // iterate through shell->vars
    // if shell->vars[i].key == key, return shell->vars[i].value
    // else return NULL
    printf("key: %s\n", key);
    for (int i = 0; shell->vars->next != NULL; i++) {
        if (my_strcmp(shell->vars->key, key) == 0)
            return shell->vars->value;
        shell->vars = shell->vars->next;
    }
    if (my_strcmp(shell->vars->key, key) == 0)
        return shell->vars->value;
    return NULL;
}

int assign_variables(cmd_t* cmd, shell_t* shell)
{
    // iterate through cmd->argv
    // if cmd->argv[i] starts with $, replace it with the value of the variable
    // also check if the value of the variable corresponds to a get_env_var value
    // if value != NULL, variable is found inside env variable, else it doesn't exist
    // if variable doesn't exist, print error message
    // if variable exists, replace cmd->argv[i] with the value of the variable
    // if variable doesn't exist, return 1
    // else return 0
    for (int i = 0; cmd->argv[i] != NULL; i++) {
        if (cmd->argv[i][0] == '$') {
            char *var = get_local_var(shell, cmd->argv[i] + 1);
            if (var == NULL) {
                printf("%s: Undefined variable.\n", cmd->argv[i] + 1);
                return 1;
            }
            cmd->argv[i] = var;
        }
    }
    return 0;
}

void run_command(cmd_t* cmd, shell_t* shell)
{
    int fd[2];
    char* path = cmd->argv[0];
    char *full_path = get_full_path(cmd->argv[0], shell);
    if(assign_variables(cmd, shell) == 1)
        return;

    if (full_path)
        path = full_path;
    if (!is_builtin(cmd->argv[0]) && not_existing(path, shell)) {
        exit(1);
        return;
    }
    if (is_builtin(cmd->argv[0])) {
        run_builtin(cmd, shell);
        exit(shell->state);
    } else {
        if (cmd->input_type != NONE)
            set_input(cmd, shell, fd);
        if (cmd->output_type != NONE)
            set_output(cmd);
        teach_child(path, cmd->argv, shell);
    }
}

void prepare_pipe(cmd_t* cmd, shell_t* shell, int fd[2])
{
    pid_t new_sub = fork();

    if (new_sub == 0) {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        run_command(cmd->next, shell);
    } else {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
    }
}

void execute(cmd_t* cmd, shell_t* shell)
{
    pid_t sub = fork();

    if (sub == 0) {
        shell->sub = getpid();
        run_command(cmd, shell);
    } else {
        waitpid(sub, &shell->state, 0);
        handle_error(shell);
    }
}
