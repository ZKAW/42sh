/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** pipe.h
*/

#ifndef PIPE_H_
#define PIPE_H_

#include <sys/types.h>

typedef struct pipe_s {
    pid_t input_pid;
    pid_t output_pid;
} pipe_t;

#endif /* !PIPE_H_ */