/*
** EPITECH PROJECT, 2022
** mini-shell1
** File description:
** mini-shell.h
*/

#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
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
#include "struct/dir.h"
#include "struct/echo.h"
#include "struct/globbing.h"
#include "struct/foreach.h"
#include "struct/if.h"

#ifndef _MINI_SHELL_H_
    #define _MINI_SHELL_H_

    #define _XOPEN_SOURCE 700

shell_t* init_shell(char** envp, char** av);
void execute(cmd_t* cmd, shell_t* shell);
int not_existing(char* path, shell_t* shell);
int handle_status(int state);
void run_builtin(cmd_t* cmd, shell_t* shell);
int is_builtin(char* path);
char* get_full_path(char* input, shell_t* shell);
int set_input(cmd_t* cmd, shell_t* shell, int fd[2]);
char **tokenize_string(char *input, char *sep);
void prepare_pipe(cmd_t* cmd, shell_t* shell, int fd[2]);
list_t* parse_command(char *cmd_str, shell_t* shell);
int set_output(cmd_t* cmd, int input_fd[2]);
list_t* reverse_cmd(list_t* head);
char** envp_cpy(char** envp);
void handle_child_error(char** argv);
char *get_prompt_prefix(void);
char *get_env_var(char **env, char *key);
void add_arg(list_t* command_array, char* arg, int is_litteral);
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
job_t *init_job(shell_t *shell, char *name, job_type_t type);
int is_pid_alive(pid_t pid);
void display_jobs(shell_t *shell, int verbose);
char *concat_path(char *path, char *filename);
int file_has_exec_rights(char *file_path);
int is_file_exist(char *file_path);
int is_file(char *file_path);
string_t* get_string(string_t* string);
shell_t* get_shell(shell_t* shell);
extern char **split_cmd(char **envp);
extern int remove_first_n_chars(char *str, int n);
extern int core_completion(char *cmd, char **arr, char ***output);
extern int cmp_sort(const void *a, const void *b);
extern int completion(char *cmd, char **envp);
extern int arrlen(char **arr);
extern char *concat_str(char *dest, char *src);
extern char* arr_to_str(char** arr, char delim);
extern int interpreter(char *str, int i);
void init_vars(shell_t* shell);
void init_special_vars(shell_t* shell);
void set_var(shell_t* shell, char* key, char* value);
void update_cwd(shell_t* shell);
int have_space(char *str);
int cmd_is_alias(cmd_t *cmd, shell_t* shell);
int check_globbing(cmd_t* cmd, shell_t* shell);
char *get_local_var(shell_t *shell, char *key);
void replace_str_to_array(char** array, char* str, int index, cmd_t* cmd);
char* get_precmd_var(shell_t* shell);
char* get_cwdcmd_var(shell_t* shell);
char* get_fignore_var(shell_t* shell);
char* get_postcmd_var(shell_t* shell);
void handle_command(list_t* list, shell_t* shell);
int replace_globber(globber_t* globbing, int index, cmd_t* cmd);
void alias_special_var(shell_t *shell);
void set_status(shell_t* shell, int ret);
void exit_detach_shm(shell_t* shell);
void safe_free(void *ptr);
char *get_shebang(char *path);
int my_execve(char* path, char **argv, char **envp);
char* array_to_str(char **cmd);
char* concatene_value(char **cmd);
char* del_after(char *str);
char* del_before(char *str);
ssize_t my_getline(char **bufferptr, shell_t* shell);
void unset_var(shell_t *shell, char *key);
extern int error_handling_set(shell_t *shell, cmd_t *cmd);
char *parse_if(char *cmd_str, list_t **command_array, shell_t *shell);
void postcmd(shell_t* shell);
void precmd(shell_t* shell);

#endif
