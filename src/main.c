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
void reverse_head(cmd_t** head);

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

void handle_command(list_t* list, shell_t* shell)
{
    cmd_t* head;
    while (list) {
        head = list->cmd;
        exec_cmd(head, shell);
        list = list->next;
    }
}

int verify_pipe(shell_t* shell)
{
    ssize_t size = 0;
    size_t len = 0;
    char* line = "";
    if (isatty(0))
        return 0;
    while (size != EOF) {
        size = getline(&line, &len, stdin);
        if (size == 1)
            continue;
        if (size == EOF)
            return 1;
        handle_command(get_command(line), shell);
    }
    return 1;
}

int main(int ac, char** av, char** envp)
{
    size_t len = 0;
    ssize_t size = 0;
    char* line = "";
    int state = 0;
    shell_t* shell = create_shell(envp);
    if (verify_pipe(shell))
        return shell->state;
    while (1) {
        print_path();
        size = getline(&line, &len, stdin);
        if (size == -1)
            my_printf("exit\n");
        if (size == 1)
            continue;
        if (!my_strcmp(line, "exit\n") || (size == EOF))
            break;
        handle_command(get_command(line), shell);
    }
    return shell->state;
}
