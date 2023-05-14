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
    #include "job.h"

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
    char* binary_name;
    char* last_path;
    int state;
    int loop;
    pid_t sub;
    pid_t pgid;
    pid_t pid;
    struct termios term;
    string_t* string;
    history_t history;
    shared_memory_t shared_status;
    var_t* vars;
    alias_t* aliases;
    char *precmd;
    char* cwdcmd;
    char* fignore;
    job_control_t *job_control;
} shell_t;

typedef struct path {
    char** list;
} path_t;

static const path_t PATHS = {NULL};

#endif /* !SHELL_H_ */
