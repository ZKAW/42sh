/*
** EPITECH PROJECT, 2022
** mini-shell2
** File description:
** redirections.c
*/


#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/my.h"
#include "../include/mini_shell.h"

ssize_t getline(char **lineptr, size_t *n, FILE *stream);

void set_output(cmd_t* cmd, shell_t* shell)
{
    int fd;
    if (!cmd->output && !cmd->is_piped)
    return;
    if (cmd->output) {
        fd = open(cmd->output, O_RDWR | cmd->append | O_CREAT, 0644);
        dup2(fd, 1);
    } else if (cmd->is_piped) {
        close(shell->fd[0]);
        dup2(shell->fd[1], 1);
        close(shell->fd[1]);
    }
}

void get_input(cmd_t* cmd)
{
    size_t len = 0;
    ssize_t size = 0;
    char** array = malloc(sizeof(char*));
    array[0] = NULL;
    char* line = "";
    int state = 0;
    while (1) {
        my_printf("? ");
        size = getline(&line, &len, stdin);
        array = array_append(array, line);
        if (my_strstr(line, cmd->input))
            break;
    }
    cmd->input = merge_array(array);
}

void set_input(cmd_t* cmd, shell_t* shell)
{
    int fd;
    if (cmd->input_type == NONE)
        return;
    if (cmd->input_type == STD) {
        get_input(cmd);
        write(shell->fd[1], cmd->input, my_strlen(cmd->input));
        close(shell->fd[1]);
        dup2(shell->fd[0], 0);
        close(shell->fd[0]);
    }
    if (cmd->input_type == FILE_PATH)
        fd = open(cmd->input, O_RDONLY);
    if (cmd->input_type == PIPE) {
        close(shell->fd[1]);
        dup2(shell->fd[0], 0);
        close(shell->fd[0]);
    }
}
