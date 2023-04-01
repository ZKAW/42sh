/*
** EPITECH PROJECT, 2022
** mini-shell1
** File description:
** mini-shell.h
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"

#ifndef _MINI_SHELL_H_
    #define _MINI_SHELL_H_

        typedef enum input {
            NONE,
            PIPE,
            FILE_PATH,
            STD,
        } fd_type;

        typedef struct shell {
            char* root;
            char** envp;
            char* last_path;
            int state;
            char** paths;
        } shell_t;

        typedef struct command {
            char* path;
            char** argv;
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

        void segfault(int code);
        void floatpoint(int code);
        shell_t* create_shell(char** envp);
        void execute(cmd_t* cmd, shell_t* shell);
        void change_directory(char** cmd, shell_t* shell);
        int not_existing(char* path, shell_t* shell);
        void handle_error(shell_t* shell);
        void run_builtin(cmd_t* cmd, shell_t* shell);
        void my_setenv(char** cmd, shell_t* shell);
        char** get_env_paths(char** envp);
        void my_unsetenv(char** cmd, shell_t* shell);
        void throw_error(char* const strerror, shell_t* shell, int ernum);
#endif
