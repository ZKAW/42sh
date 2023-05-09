/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** command
*/

#ifndef COMMAND_H_
    #define COMMAND_H_

    #define MAX_ARGS 256
    #define FD_STATUS 10

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
    char* argv[256];
    char* output;
    char* input;
    char* full_output;
    fd_type input_type;
    fd_type output_type;
    int append;
    struct command* next;
    struct command* prev;
} cmd_t;

typedef struct command_array {
    cmd_t* cmd;
    condition_t condition;
    struct command_array* next;
    struct command_array* prev;
    bool is_background;
} list_t;

#endif /* !COMMAND_H_ */
