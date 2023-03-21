/*
** EPITECH PROJECT, 2022
** mini-shell2
** File description:
** redirections.c
*/


#include <fcntl.h>
#include <unistd.h>
#include "../include/my.h"
#include "../include/mini_shell.h"

void set_output(cmd_t* cmd)
{
    int fd;
    if (cmd->output != NULL) {
        fd = open(cmd->output, O_RDWR | cmd->append | O_CREAT, 0644);
        dup2(fd, 1);
        close(fd);
    }
}

void set_input(cmd_t* cmd)
{
    int fd;
    if (cmd->input) {
        fd = open(cmd->input, O_RDONLY);
        dup2(fd, 0);
        close(fd);
    }
}
