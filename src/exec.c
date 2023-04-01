/*
** EPITECH PROJECT, 2022
** mini-shell1
** File description:
** exec.c
*/

#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include "../include/my.h"
#include "../include/mini_shell.h"

int kill(pid_t pid, int sig);
char* get_full_path(char* input, shell_t* shell);
void set_output(cmd_t* cmd, shell_t* shell, int fd[2]);
void set_input(cmd_t* cmd, shell_t* shell, int fd[2]);
void run_command(cmd_t* cmd, shell_t* shell);
int is_builtin(char* path);

void handle_child_error(char** argv, shell_t* shell)
{
    if (errno == 8) {
        write(2, argv[0], my_strlen(argv[0]));
        write(2, ": Exec format error. Wrong Architecture.\n", 41);
    }
    if (errno == 13) {
        write(2, argv[0], my_strlen(argv[0]));
        write(2, ": Permission denied.\n", 21);
    }
    exit(1);
}

void teach_child(char* path, char** cmd, shell_t* shell)
{
    int state = execve(path, cmd, shell->envp);
    if (state == -1) {
        handle_child_error(cmd, shell);
    }
}

void prepare_pipe(cmd_t* cmd, shell_t* shell, int fd[2])
{
    pid_t new_sub;
    new_sub = fork();
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

void run_command(cmd_t* cmd, shell_t* shell)
{
    int fd[2];
    char* path;
    if (!is_builtin(cmd->argv[0]) && !is_include('/', cmd->argv[0])
    && !is_include('\\', cmd->argv[0]))
        path = get_full_path(cmd->argv[0], shell);
    else
        path = cmd->argv[0];
    if (!path && !is_builtin(cmd->argv[0]) && not_existing(cmd->argv[0], shell))
        return;
    if (is_builtin(cmd->argv[0])) {
        run_builtin(cmd, shell);
        exit(shell->state);
    }   else {
        if (cmd->input_type != NONE)
            set_input(cmd, shell, fd);
        if (cmd->output_type != NONE)
            set_output(cmd, shell, fd);
        teach_child(path, cmd->argv, shell);
    }
}

void execute(cmd_t* cmd, shell_t* shell)
{
    pid_t sub;
    sub = fork();
    if (sub == 0)
        run_command(cmd, shell);
    else {
        waitpid(sub, &shell->state, 0);
        handle_error(shell);
    }
}
