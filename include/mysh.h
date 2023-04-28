/*
** EPITECH PROJECT, 2022
** mini-shell1
** File description:
** mini-shell.h
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

#include "lib.h"
#include "builtin.h"
#include "struct/command.h"
#include "struct/shell.h"
#include "macro/utils.h"

#ifndef _MINI_SHELL_H_
    #define _MINI_SHELL_H_

shell_t* init_shell(char** envp);
void execute(cmd_t* cmd, shell_t* shell);
int not_existing(char* path, shell_t* shell);
void handle_error(shell_t* shell);
void run_builtin(cmd_t* cmd, shell_t* shell);
char** get_env_paths(char** envp);
void builtin_cd(char** cmd, shell_t* shell);
void builtin_setenv(char** cmd, shell_t* shell);
void builtin_unsetenv(char** cmd, shell_t* shell);
void builtin_env(char** cmd, shell_t* shell);
void builtin_exit(char** cmd, shell_t* shell);
int is_builtin(char* path);
char* get_full_path(char* input, shell_t* shell);
int set_input(cmd_t* cmd, shell_t* shell, int fd[2]);
char **tokenize_string(char *input, char *sep);
void prepare_pipe(cmd_t* cmd, shell_t* shell, int fd[2]);
cmd_t* parse_command(char* input, cmd_t* next);
list_t* split_pipes(char* input, list_t* next);
list_t* get_command(char * str);
void parse_output(cmd_t* command);
void parse_input(cmd_t* command);
void set_output(cmd_t* cmd);
list_t* reverse_cmd(list_t* head);
char** envp_cpy(char** envp);

#endif
