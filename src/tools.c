/*
** EPITECH PROJECT, 2022
** mini-shell1
** File description:
** tools.c
*/

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "../include/my.h"
#include "../include/mini_shell.h"

int is_builtin(char* path);
void enable_raw_mode(struct termios* raw);
void disable_raw_mode(struct termios* raw);

char** get_env_paths(char** envp)
{
    int i;
    char** paths;
    for (i = 0; my_strncmp(envp[i], "PATH", 4); i++);
    paths = string_split(&envp[i][5], ":");
    for (i = 0; paths[i] != NULL; i++)
        paths[i] = str_append(paths[i], "/");
    return paths;
}

char** envp_cpy(char** envp)
{
    int i;
    char** copy = malloc(sizeof(char*) * (my_arraylen(envp) + 1));
    for (i = 0; envp[i]; i++)
        copy[i] = my_strdup(envp[i]);
    copy[i] = NULL;
    return copy;
}

shell_t* create_shell(char** envp)
{
    shell_t* shell = malloc(sizeof(shell_t));
    shell->root = malloc(sizeof(char) * 500);
    shell->root = getcwd(shell->root, 500);
    shell->envp = envp_cpy(envp);
    shell->last_path = malloc(sizeof (char) * 500);
    shell->state = 0;
    shell->is_navigating = 0;
    shell->paths = get_env_paths(envp);
    shell->history = NULL;
    return shell;
}

int not_existing(char* path, shell_t* shell)
{
    write(2, path, my_strlen(path));
    write (2, ": Command not found.\n", 21);
    shell->state = 1;
    return 1;
}

void handle_error(shell_t* shell)
{
    int state;
    if (WIFSIGNALED(shell->state)) {
        if (WTERMSIG(shell->state) == SIGSEGV)
            write(2, "Segmentation fault", 18);
        if (WTERMSIG(shell->state) == SIGFPE)
            write(2, "Floating exception", 18);
        if (WCOREDUMP(shell->state))
            write(2, " (core dumped)", 14);
        write(2, "\n", 1);
    }
    if (shell->state == 256 || shell->state == 15)
        shell->state = 1;
}
