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

char* render_backtick(char* const str)
{
    char* content;
    char** args = tokenize_string(str, " \t\n");
    int fd[2], pid, status;
    int result, duplicate;
    size_t size;
    pipe(fd);
    pid = fork();
    if (pid == 0) {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        execve("/bin/ls", args, NULL);
    } else {
        close(fd[1]);
        waitpid(pid, &status, 0);
        content = store_output(fd[0]);
    }
    return content;
}