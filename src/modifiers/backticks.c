/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** backticks.c
*/

#include "mysh.h"

void handle_command(list_t* list, shell_t* shell);

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
    int fd[2], pid, status;
    pipe(fd);
    pid = fork();
    if (pid == 0) {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        handle_command(parse_command(str, shell), shell);
        exit(shell->state);
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
        add_arg(*command_array, args[i], BACKTICKS);
    return cmd_str;
}
