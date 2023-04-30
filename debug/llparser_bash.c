#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_ARGS 32
#define MAX_COMMANDS 8

typedef struct {
    char *args[MAX_ARGS + 1];
    int in_fd;
    int out_fd;
} Command;

typedef struct {
    Command commands[MAX_COMMANDS];
    int num_commands;
} Pipeline;

void error(char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

int is_whitespace(char c) {
    return (c == ' ' || c == '\t' || c == '\n');
}

char *skip_whitespace(char *str) {
    while (is_whitespace(*str))
        str++;
    return str;
}

char *skip_non_whitespace(char *str) {
    while (*str && !is_whitespace(*str))
        str++;
    return str;
}

char *copy_until(char *dst, char *src, char *delim) {
    while (*src && !strchr(delim, *src))
        *(dst++) = *(src++);
    *dst = '\0';
    return src;
}

void parse_command(char *cmd_str, Command *cmd) {
    int argc = 0;

    // Set input and output file descriptors to default values
    cmd->in_fd = STDIN_FILENO;
    cmd->out_fd = STDOUT_FILENO;

    // Parse arguments
    while (*cmd_str && argc < MAX_ARGS) {
        cmd_str = skip_whitespace(cmd_str);
        if (*cmd_str == '\0')
            break;
        if (*cmd_str == '>') {
            // Output redirection
            cmd_str = skip_whitespace(cmd_str + 1);
            if (*cmd_str == '\0')
                error("Missing output file name after >");
            char out_file[256];
            cmd_str = copy_until(out_file, cmd_str, " \t\n");
            cmd->out_fd = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (cmd->out_fd == -1)
                error("Could not open output file");
        } else if (*cmd_str == '<') {
            // Input redirection
            cmd_str = skip_whitespace(cmd_str + 1);
            if (*cmd_str == '\0')
                error("Missing input file name after <");
            char in_file[256];
            cmd_str = copy_until(in_file, cmd_str, " \t\n");
            cmd->in_fd = open(in_file, O_RDONLY);
            if (cmd->in_fd == -1)
                error("Could not open input file");
        } else {
            // Regular argument
            char arg[256];
            cmd_str = copy_until(arg, cmd_str, "><| \t\n");
            cmd->args[argc] = strdup(arg);
            argc++;
        }
    }

    if (argc == 0)
        error("Empty command");

    cmd->args[argc] = NULL;
}

void parse_pipeline(char *pipeline_str, Pipeline *pipeline) {
    pipeline->num_commands = 0;

    // Parse commands
    while (*pipeline_str && pipeline->num_commands < MAX_COMMANDS) {
        pipeline_str = skip_whitespace(pipeline_str);
        if (*pipeline_str == '\0')
            break;
        char cmd_str[1024];
        pipeline_str = copy_until(cmd_str, pipeline_str, "|");
        parse_command(cmd_str, &pipeline->commands[pipeline->num_commands]);
        pipeline->num_commands++;
        if (*pipeline_str == '|')
            pipeline_str++;
    }

    if (pipeline->num_commands == 0)
        error("Empty pipeline");
}

void execute_pipeline(Pipeline *pipeline) {
    int i;
    int in_fd = STDIN_FILENO;
    int out_fd = STDOUT_FILENO;
    int pipe_fds[2];

    for (i = 0; i < pipeline->num_commands; i++) {
        Command *cmd = &pipeline->commands[i];

        // Set input file descriptor
        if (cmd->in_fd != STDIN_FILENO) {
            in_fd = cmd->in_fd;
        }

        // Set output file descriptor
        if (i < pipeline->num_commands - 1) {
            // Create pipe
            if (pipe(pipe_fds) == -1)
                error("Could not create pipe");
            out_fd = pipe_fds[1];
        } else {
            // Last command
            if (cmd->out_fd != STDOUT_FILENO) {
                out_fd = cmd->out_fd;
            }
        }

        // Fork
        pid_t pid = fork();
        if (pid == -1)
            error("Could not fork");

        if (pid == 0) {
            // Child process
            if (in_fd != STDIN_FILENO) {
                // Redirect input
                if (dup2(in_fd, STDIN_FILENO) == -1)
                    error("Could not redirect input");
                close(in_fd);
            }
            if (out_fd != STDOUT_FILENO) {
                // Redirect output
                if (dup2(out_fd, STDOUT_FILENO) == -1)
                    error("Could not redirect output");
                close(out_fd);
            }
            // Execute command
            execvp(cmd->args[0], cmd->args);
            error("Could not execute command");
        } else {
            // Parent process
            if (in_fd != STDIN_FILENO)
                close(in_fd);
            if (out_fd != STDOUT_FILENO)
                close(out_fd);
            in_fd = pipe_fds[0];
            out_fd = STDOUT_FILENO;
        }
    }

    // Wait for last child process
    wait(NULL);
}

int main(int argc, char *argv[]) {
    char line[1024];
    Pipeline pipeline;

    while (1) {
        // Print prompt
        if (isatty(STDIN_FILENO))
            printf("shell> ");
        fflush(stdout);

        // Read line
        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        if (is_whitespace(*line))
            continue;

        // Parse pipeline
        parse_pipeline(line, &pipeline);

        // Execute pipeline
        execute_pipeline(&pipeline);
    }

    return 0;
}
