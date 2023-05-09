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

typedef struct alias_s {
    char *alias;
    char *command;
    struct alias_s *next;
} alias_t;

typedef struct var {
    char* key;
    char* value;
    struct var* next;
} var_t;

typedef struct shell {
    char* root;
    char** envp;
    char* last_path;
    int state;
    char** paths;
    pid_t sub;
    struct termios term;
    string_t* string;
    history_t history;
    var_t* vars;
    alias_t *aliases;
} shell_t;

typedef struct path {
    char** list;
} path_t;

static const path_t PATHS = {NULL};

#endif /* !SHELL_H_ */
