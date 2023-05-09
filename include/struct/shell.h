/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** shell
*/

#ifndef SHELL_H_
    #define SHELL_H_

    #include <sys/types.h>
    #include <termios.h>
    #include "line.h"
    #include "memory.h"

typedef struct shell {
    char* root;
    char** envp;
    char* last_path;
    int state;
    char** paths;
    pid_t sub;
    pid_t pgid;
    struct termios term;
    string_t* string;
    history_t history;
    shared_memory_t shared_status;
    __sighandler_t sigtstp_handler;
    __sighandler_t sigcont_handler;
} shell_t;

typedef struct path {
    char** list;
} path_t;

static const path_t PATHS = {NULL};

#endif /* !SHELL_H_ */
