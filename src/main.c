/*
** EPITECH PROJECT, 2022
** mini-shell1
** File description:
** main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <string.h>
#include "../include/my.h"
#include "../include/mini_shell.h"

void print_env(char** cmd, shell_t* shell);
list_t* get_command(char * str);

void print_path(void)
{
    char path[500];
    getcwd(path, 500);
    my_printf("%s $> ", path);
}

void exec_cmd(cmd_t* cmd, shell_t* shell)
{
    int i;
    char** argv = cmd->argv;
    char* cmd_names[5] = {"cd", "env", "setenv", "unsetenv", NULL};
    void (*cmd_funcs[5]) (char** cmd, shell_t* shell) = {
        change_directory, print_env, my_setenv, my_unsetenv
    };
    for (i = 0; i < 4 && my_strcmp(cmd_names[i], argv[0]); i++);
    if (i < 4)
        (cmd_funcs[i])(argv, shell);
    else
        execute(cmd, shell);
}

void dump_cmd(cmd_t* cmd)
{
    while (cmd) {
        my_printf("path: %s\n", cmd->path);
        dump_args(cmd->argv);
        my_printf("pipe to next: %s\n", cmd->is_piped ? "yes" : "no");
        my_printf("redirect: %s\n", cmd->output ? cmd->output : "no");
        if (cmd->output) {
            my_printf("%s\n", cmd->append == O_APPEND ?
            "apend to file" : "overwrite text");
        }
        if (cmd->input) {
            my_printf("take %s as input\n", cmd->input);
        }
        cmd = cmd->next;
    }
}

void pipe_work(cmd_t* head, shell_t* shell)
{
    while (head) {
        exec_cmd(head, shell);
        head = head->next;
    }
}

int main(int ac, char** av, char** envp)
{
    size_t len = 0;
    ssize_t size = 0;
    char* line = "";
    int state = 0;
    cmd_t *head;
    list_t* list;
    shell_t* shell = create_shell(envp);
    while (1) {
        print_path();
        size = getline(&line, &len, stdin);
        list = get_command(line);
        while (list) {
            head = list->cmd;
            pipe_work(head, shell);
            list = list->next;
        }
    }
    return shell->state;
}
