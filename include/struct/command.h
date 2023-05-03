/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** command
*/

#ifndef COMMAND_H_
    #define COMMAND_H_

        #define MAX_ARGS 256

typedef enum {
    NONE,
    PIPE,
    FILE_PATH,
    STD,
} fd_type;

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
    struct command_array* next;
} list_t;

#endif /* !COMMAND_H_ */
