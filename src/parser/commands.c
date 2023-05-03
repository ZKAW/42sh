/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** commands
*/

#include "mysh.h"

int is_char_whitespace(char c);
char *skip_whitespace(char *str);
char *skip_non_whitespace(char *str);
char *copy_until(char *dst, char *src, char *delim);
char* parse_file_name(char** cmd_str);

void set_pipe_attributes(cmd_t* cmd)
{
    cmd_t *tmp = cmd;
    cmd = cmd->next;
    while (cmd) {
        cmd->output_type = PIPE;
        cmd = cmd->next;
    }
    while (tmp->next) {
        tmp->input_type = PIPE;
        tmp = tmp->next;
    }
}

void dump_args(char** args)
{
    printf("args: ");
    while (*args) {
        printf("%s ", *args);
        args++;
    }
    printf("\n");
}

void dump_cmd(cmd_t* cmd)
{
    while (cmd) {
        printf("path: %s\n", cmd->path);
        dump_args(cmd->argv);
        printf("pipe to next: %s\n", cmd->output_type == PIPE ? "yes" : "no");
        printf("pipe from prev: %s\n", cmd->input_type == PIPE ? "yes" : "no");
        printf("redirect: %s\n", cmd->output ? cmd->output : "no");
        if (cmd->output) {
            printf("%s\n", cmd->append == O_APPEND ?
            "append to file" : "overwrite text");
        }
        if (cmd->input) {
            printf("take %s as input\n", cmd->input);
        }
        my_putchar('\n');
        cmd = cmd->next;
    }
}

list_t* split_pipes(char *pipeline_str, list_t* arr_next)
{
    char cmd_str[1024];
    list_t* command_array = malloc(sizeof(list_t));
    command_array->next = arr_next;
    cmd_t* cmd, *next = NULL;
    while (*pipeline_str) {
        pipeline_str = skip_whitespace(pipeline_str);
        if (*pipeline_str == '\0')
            break;
        pipeline_str = copy_until(cmd_str, pipeline_str, "|");
        cmd = malloc(sizeof(cmd_t));
        parse_command(cmd_str, cmd);
        cmd->next = next;
        next = cmd;
        if (*pipeline_str == '|')
            pipeline_str++;
    }
    set_pipe_attributes(cmd);
    command_array->cmd = cmd;
    return command_array;
}

list_t* get_command(char * str)
{
    list_t* command_array = NULL;
    char delimiters[] = ";";
    char *command_position = strtok(str, delimiters);
    str = clean_str(str);
    while (command_position) {
        command_array = split_pipes(command_position, command_array);
        if (command_array == NULL)
            return NULL;
        command_position = strtok(NULL, delimiters);
    }
    command_array = reverse_cmd(command_array);
    return command_array;
}
