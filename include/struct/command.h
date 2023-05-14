/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** command
*/

#ifndef COMMAND_H_
    #define COMMAND_H_

    #define QUOTTED 1
    #define BACKTICKS 1
    #define SIMPLE 0
    #define MAX_ARGS 256
    #define FD_STATUS 10
    #define BUILTIN_ERROR -84

typedef struct command_array list_t;
typedef struct foreach foreach_t;
typedef struct job_s job_t;
typedef struct if_s if_t;

typedef enum {
    NONE,
    PIPE,
    FILE_PATH,
    STD,
} fd_type;

typedef enum CONDITION {
    AND = 1,
    OR,
} condition_t;

typedef struct command {
    int argc;
    char* path;
    char** argv;
    int* arg_type;
    char* output;
    char* input;
    char* full_output;
    fd_type input_type;
    fd_type output_type;
    int append;
    list_t* subshell;
    foreach_t* foreach;
    if_t* if_statement;
    job_t* job;
    struct command* next;
    struct command* prev;
} cmd_t;

typedef struct command_array {
    cmd_t* cmd;
    condition_t condition;
    struct command_array* next;
    struct command_array* prev;
    int in_subshell;
} list_t;

#endif /* !COMMAND_H_ */
