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
void prepare_pipe(cmd_t* cmd, shell_t* shell, int fd[2]);
int is_builtin(char* path);
void execute(cmd_t* cmd, shell_t* shell);

void print_path(void)
{
    char path[500];
    getcwd(path, 500);
    my_printf("%s $> ", path);
}

void handle_command(list_t* list, shell_t* shell)
{
    cmd_t* head;
    if (list == NULL) {
        my_printf("Invalid null command.\n");
        shell->state = 1;
    }
    while (list) {
        head = list->cmd;
        if (is_builtin(head->path))
            run_builtin(head, shell);
        if (is_builtin(head->path) && !head->next)
            return;
        execute(head, shell);
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
        if (size == 1)
            continue;
        if (my_strstr(line, "exit") || (size == EOF)) {
            my_printf("exit\n");
            break;
        }
        handle_command(get_command(line), shell);
    }
    return shell->state;
}
