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
#include <sys/shm.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>
#include <stdbool.h>

#include "lib.h"
#include "builtin.h"
#include "struct/command.h"
#include "struct/shell.h"
#include "struct/pipe.h"
#include "macro/utils.h"
#include "macro/cmd.h"

#ifndef _MINI_SHELL_H_
    #define _MINI_SHELL_H_

    #define _XOPEN_SOURCE 700

shell_t* init_shell(char** envp);
void execute(cmd_t* cmd, shell_t* shell);
int not_existing(char* path, shell_t* shell);
int handle_status(int state);
void run_builtin(cmd_t* cmd, shell_t* shell);
char** get_env_paths(char** envp);
int is_builtin(char* path);
char* get_full_path(char* input, shell_t* shell);
int set_input(cmd_t* cmd, shell_t* shell, int fd[2]);
char **tokenize_string(char *input, char *sep);
void prepare_pipe(cmd_t* cmd, shell_t* shell, int fd[2]);
list_t* parse_command(char *cmd_str, shell_t* shell);
void set_output(cmd_t* cmd, int input_fd[2]);
list_t* reverse_cmd(list_t* head);
char** envp_cpy(char** envp);
void handle_child_error(char** argv);
char *get_prompt_prefix(void);
char *get_env_var(char **env, char *key);
char *copy_until(char *dst, char *src, char *delim);
void error(char *msg);
void throw_error(char* const strerror, shell_t* shell, int ernum);
shared_memory_t create_shm(int shared_var);
void detach_shm(shared_memory_t shared_memory);
char *parse_bg(char *cmd_str, list_t **command_array, shell_t *shell);
shell_t* get_shell(shell_t* shell);
list_t* append_list(list_t* array);
cmd_t* append_command(list_t* array);
void close_cmd(cmd_t* cmd);
void add_job(shell_t *shell, job_t *job);
void set_job_status(shell_t *shell, job_t *job, job_status_t status);
job_t *init_job(shell_t *shell, char *name);
int is_pid_alive(pid_t pid);

#endif
