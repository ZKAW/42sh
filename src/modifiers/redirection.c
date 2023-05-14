/*
** EPITECH PROJECT, 2022
** mini-shell2
** File description:
** redirection.c
*/

#include "mysh.h"

void get_input(cmd_t* cmd)
{
    size_t len = 0;
    char** array = malloc(sizeof(char*));
    array[0] = NULL;
    char* line = "";

    while (1) {
        printf("? ");
        getline(&line, &len, stdin);
        array = array_append(array, line);
        if (strstr(line, cmd->input))
            break;
    }
    cmd->input = merge_array(array);
}

void guarantee_pipe(int fd[2], shell_t* shell)
{
    if (pipe(fd) == -1) {
        kill(shell->sub, SIGTERM);
        exit(1);
    }
}

int set_input(cmd_t* cmd, shell_t* shell, int fd[2])
{
    int file_fd;
    if (cmd->input_type == NONE) return 0;
    if (cmd->input_type == FILE_PATH) {
        file_fd = open(cmd->input, O_RDONLY);
        dup2(file_fd, 0);
        return file_fd;
    }
    guarantee_pipe(fd, shell);
    if (cmd->input_type == STD) {
        get_input(cmd);
        write(fd[1], cmd->input, my_strlen(cmd->input));
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
    }
    if (is_builtin(cmd->path)) return 0;
    if (cmd->input_type == PIPE) {
        prepare_pipe(cmd, shell, fd); return fd[0];
    }
    return 1;
}

int set_output(cmd_t* cmd, int output_fd[2])
{
    int file_fd;
    if (cmd->output_type == FILE_PATH) {
        file_fd = open(cmd->output, O_RDWR | cmd->append | O_CREAT, 0644);
        dup2(file_fd, 1);
        return file_fd;
    }
    if (cmd->output_type == PIPE) {
        dup2(output_fd[1], 1);
        close(output_fd[1]);
        return output_fd[1];
    }
    return 1;
}
