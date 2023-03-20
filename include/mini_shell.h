/*
** EPITECH PROJECT, 2022
** mini-shell1
** File description:
** mini-shell.h
*/

#ifndef _MINI_SHELL_H_
    #define _MINI_SHELL_H_

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
            char* std_output;
            char* full_output;
            int is_piped;
            struct command* next;
        } cmd_t;

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
