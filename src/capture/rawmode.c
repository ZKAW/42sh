/*
** EPITECH PROJECT, 2022
** bootstrap42
** File description:
** rawmode.c
*/


#include "mysh.h"
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>


void enable_raw_mode(struct termios* raw)
{
    int flags;
    tcgetattr(STDIN_FILENO, raw);
    raw->c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, raw);
    flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

void disable_raw_mode(struct termios* raw)
{
    tcgetattr(STDIN_FILENO, raw);
    raw->c_lflag |= (ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, raw);
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
}

void ctrl_c_handler(int sig, volatile int *buffer_empty)
{
    (void)sig;
    if (!(*buffer_empty)) {
        write(STDOUT_FILENO, "Ctrl+C detected\n", 16);
    }
}