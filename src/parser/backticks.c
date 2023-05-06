/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** backticks.c
*/

#include "mysh.h"

char* store_output(int fd)
{
    ssize_t nread;
    char buf[4096];
    char *content = malloc(4096);
    size_t size = 0;
    while ((nread = read(fd, buf, 4096)) > 0) {
        memcpy(content + size, buf, nread);
        size += nread;
        content = realloc(content, size + 4096);
    }
    content[size] = '\0';
    return content;
}

char* render_backtick(char* const str, shell_t* shell)
{
    char* content;
    char** args = tokenize_string(str, " \t\n");
    char* path = get_full_path(args[0], shell);
    int fd[2], pid, status;
    pipe(fd);
    pid = fork();
    if (pid == 0) {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        execve(path, args, NULL);
    } else {
        close(fd[1]);
        waitpid(pid, &status, 0);
        content = store_output(fd[0]);
    }
    return content;
}

char* parse_backticks(char* cmd_str, list_t** command_array, shell_t* shell)
{
    cmd_t* cmd = (*command_array)->cmd;
    char command[4096] = {0};
    char *content, **args;
    while (*cmd_str != '`') {
        strncat(command, cmd_str, 1);
        cmd_str++;
    }
    cmd_str++;
    content = render_backtick(command, shell);
    args = tokenize_string(content, " \t\n");
    for (int i = 0; args[i]; i++)
        cmd->argv[cmd->argc++] = strdup(args[i]);
    return cmd_str;
}
