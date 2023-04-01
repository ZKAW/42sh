/*
** EPITECH PROJECT, 2022
** mini-shell2
** File description:
** redirections.c
*/


#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/my.h"
#include "../include/mini_shell.h"

ssize_t getline(char **lineptr, size_t *n, FILE *stream);
void prepare_pipe(cmd_t* cmd, shell_t* shell, int fd[2]);

void set_output(cmd_t* cmd, int fd[2], shell_t* shell)
{
    int output_fd;
    if (cmd->output_type == FILE_PATH) {
        output_fd = open(cmd->output, O_RDWR | cmd->append | O_CREAT, 0644);
        dup2(output_fd, 1);
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

void set_input(cmd_t* cmd, shell_t* shell, int fd[2])
{
    int file_fd;
    if (pipe(fd) == -1) {
        perror(NULL);
        exit(1);
    }
    if (cmd->input_type == STD) {
        get_input(cmd);
        write(fd[1], cmd->input, my_strlen(cmd->input));
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
    }
    if (cmd->input_type == FILE_PATH) {
        file_fd = open(cmd->input, O_RDONLY);
        dup2(file_fd, 0);
    }
    if (cmd->input_type == PIPE) {
        prepare_pipe(cmd, shell, fd);
    }
}
