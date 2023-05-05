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

list_t* get_command(char * str)
{
    list_t* command_array = NULL, *next = NULL;
    char delimiters[] = ";";
    char *command_position = strtok(str, delimiters);
    str = clean_str(str);
    while (command_position) {
        command_array = malloc(sizeof(list_t));
        command_array->cmd = NULL;
        parse_command(command_position, command_array);
        command_array->next = next;
        next = command_array;
        if (command_array == NULL)
            return NULL;
        command_position = strtok(NULL, delimiters);
    }
    command_array = reverse_cmd(command_array);
    return command_array;
}