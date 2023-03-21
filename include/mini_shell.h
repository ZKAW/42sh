/*
** EPITECH PROJECT, 2022
** mini-shell1
** File description:
** mini-shell.h
*/

#ifndef _MINI_SHELL_H_
    #define _MINI_SHELL_H_

        typedef enum input {
            NONE,
            PIPE,
            FILE_PATH,
            STD,
        } input_type;

        typedef struct shell {
            char* root;
            char** envp;
            char* last_path;
            int state;
            char** paths;
            int fd[2];
        } shell_t;

        typedef struct command {
            char* path;
            char** argv;
            char* output;
            char* input;
            char* full_output;
            input_type input_type;
            int is_piped;
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
        int is_existing(char* path);
        void handle_error(shell_t* shell);
        void my_setenv(char** cmd, shell_t* shell);
        char** get_env_paths(char** envp);
        void my_unsetenv(char** cmd, shell_t* shell);
        void throw_error(char* const strerror, shell_t* shell, int ernum);
#endif
