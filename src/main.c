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
#include <string.h>
#include "../include/my.h"
#include "../include/mini_shell.h"

void print_env(char** cmd, shell_t* shell);
cmd_t* get_command(char * str);

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

void dump_args(char** argv)
{
    if (!argv[1])
        my_printf("no args");
    else
        my_printf("args: ");
    for (int i = 1; argv[i]; i++)
        my_printf("%s ", argv[i]);
    my_putchar('\n');
}

void dump_cmd(cmd_t* cmd)
{
    while (cmd) {
        my_printf("path: %s\n", cmd->path);
        dump_args(cmd->argv);
        my_printf("pipe to next: %s\n", cmd->is_piped ? "yes" : "no");
        my_printf("redirect: %s\n", cmd->std_output ? cmd->std_output : "no");
        my_printf("\n");
        cmd = cmd->next;
    }
}

int main(int ac, char** av, char** envp)
{
    size_t len = 0;
    ssize_t size = 0;
    char* line = "";
    int state = 0;
    shell_t* shell = create_shell(envp);
    while (1) {
        print_path();
        size = getline(&line, &len, stdin);
        cmd_t* cmd = get_command(line);
        while (cmd) {
            exec_cmd(cmd, shell);
            cmd = cmd->next;
        }
    }
    return shell->state;
}
