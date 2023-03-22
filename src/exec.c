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
void set_output(cmd_t* cmd, shell_t* shell);
void set_input(cmd_t* cmd, shell_t* shell);

void handle_child_error(char** argv)
{
    if (errno == 8) {
        write(2, argv[0], my_strlen(argv[0]));
        write(2, ": Exec format error. Binary file not executable.\n", 49);
    }
    if (errno == 13) {
        write(2, argv[0], my_strlen(argv[0]));
        write(2, ": Permission denied.\n", 21);
    }
}

void teach_child(char* path, char** cmd, shell_t* shell)
{
    int state;
    state = execve(path, cmd, shell->envp);
    if (state == -1) {
        handle_child_error(cmd);
        exit(1);
    }
}

char* get_full_path(char* input, shell_t* shell)
{
    char** paths = shell->paths;
    char* test_path;
    int input_s = my_strlen(input);
    for (int i = 0; paths[i]; i++) {
        test_path = malloc(sizeof(char) * (my_strlen(paths[i]) + input_s + 1));
        my_strcpy(test_path, paths[i]);
        my_strcat(test_path, input);
        if (is_existing(test_path))
            return test_path;
        free(test_path);
    }
    return NULL;
}

void run_command(cmd_t* cmd, shell_t* shell)
{
    pid_t sub;
    if (cmd->output_type == PIPE || cmd->input_type == STD)
        pipe(shell->fd);
    sub = fork();
    if (sub == 0) {
        set_output(cmd, shell);
        set_input(cmd, shell);
        teach_child(cmd->path, cmd->argv, shell);
    } else {
        if (cmd->output_type == PIPE)
            close(shell->fd[1]);
        if (cmd->input_type == PIPE || cmd->input_type == FILE_PATH)
            close(shell->fd[0]);
        if (cmd->input_type == STD) {
            close(shell->fd[0]);
            close(shell->fd[1]);
        }
        waitpid(sub, &shell->state, 0);
        handle_error(shell);
    }
}

void execute(cmd_t* cmd, shell_t* shell)
{
    int state;
    ssize_t ret;
    if (!is_include('/', cmd->argv[0]) && !is_include('\\', cmd->argv[0]))
        cmd->path = get_full_path(cmd->argv[0], shell);
    else
        cmd->path = cmd->argv[0];
    if (!is_existing(cmd->path)) {
        my_printf("%s: Command not found.\n", cmd[0]);
        shell->state = 1;
        return;
    }
    run_command(cmd, shell);
}
