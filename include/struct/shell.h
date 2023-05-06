/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** shell
*/

#ifndef SHELL_H_
    #define SHELL_H_

    #include <sys/types.h>

typedef struct shell {
    char* root;
    char** envp;
    char* last_path;
    int state;
    char** paths;
    pid_t sub;
} shell_t;

typedef struct path {
    char** list;
} path_t;

static const path_t PATHS = {NULL};

#endif /* !SHELL_H_ */
