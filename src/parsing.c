/*
** EPITECH PROJECT, 2022
** my_str_to_word_array.c
** File description:
** task04
*/

#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../include/my.h"
#include "../include/mini_shell.h"

char* clean_str(char* line);
cmd_t* reverse_cmd(cmd_t* head);

void parse_output(cmd_t* command)
{
    int append, overwrite;
    for (int i = 0; command->argv[i] != NULL; i++) {
        overwrite = my_strcmp(">", command->argv[i]);
        append = my_strcmp(">>", command->argv[i]);
        if (!overwrite || !append) {
            command->output = command->argv[i + 1];
            command->argv = array_remove(i, command->argv);
            command->argv = array_remove(i, command->argv);
        }
        if (!append)
            command->append = O_APPEND;
        if (!append || !overwrite)
            break;
    }
}

void parse_input(cmd_t* command)
{
    int file;
    for (int i = 0; command->argv[i] != NULL; i++) {
        file = my_strcmp("<", command->argv[i]);
        if (!file) {
            command->input = command->argv[i + 1];
            command->argv = array_remove(i, command->argv);
            command->argv = array_remove(i, command->argv);
            break;
        }
    }
}

cmd_t* parse_command(char* input, cmd_t* next, char* original)
{
    char* token;
    cmd_t* command = malloc(sizeof(cmd_t));
    command->argv = string_split(input, ' ');
    command->path = command->argv[0];
    command->append = O_TRUNC;
    command->output = NULL;
    command->input = NULL;
    parse_output(command);
    parse_input(command);
    if (original[my_strlen(input)] == '|')
            command->is_piped = 1;
    else
        command->is_piped = 0;
    command->next = next;
    return command;
}

cmd_t* get_command(char * str)
{
    cmd_t *command = NULL;
    char delimiters[] = ";|";
    char *command_position, *original;
    str = clean_str(str);
    original = my_strdup(str);
    command_position = strtok(str, delimiters);
    while (command_position) {
        command = parse_command(command_position, command, original);
        command_position = strtok(NULL, delimiters);
    }
    command = reverse_cmd(command);
    return command;
}
