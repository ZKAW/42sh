/*
** EPITECH PROJECT, 2022
** my_str_to_word_array.c
** File description:
** task04
*/

#include <string.h>
#include <stdlib.h>
#include "../include/my.h"
#include "../include/mini_shell.h"

char** command_split(char * str)
{
    int count = 0;
    char delimiters[] = " \t";
    char *token = strtok(str, delimiters);
    char **argv = malloc(sizeof(char*));
    argv[0] = NULL;
    while (token != NULL) {
        argv = array_append(argv, token);
        token = strtok(NULL, delimiters);
    }
    return argv;
}

char* clean_str(char* line)
{
    char* tmp = malloc(sizeof(char) * (my_strlen(line) + 1));
    if (line[my_strlen(line) - 1] == '\n')
        my_strncpy(tmp, line, my_strlen(line) - 1);
    else
        my_strcpy(tmp, line);
    return tmp;
}

cmd_t* parse_command(char* input, cmd_t* next)
{
    char* token;
    cmd_t* command = malloc(sizeof(cmd_t));
    char** redirection = string_split(input, '>');
    command->argv = string_split(redirection[0], ' ');
    command->path = command->argv[0];
    command->std_output = redirection[1];
    command->is_piped = 0;
    command->next = next;
    return command;
}

cmd_t* reverse_cmd(cmd_t* head)
{
    cmd_t *current = head, *prev = NULL, *next = NULL, *new_head = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
    return head;
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
        command = parse_command(command_position, command);
        if (original[my_strlen(command_position)] == '|')
            command->is_piped = 1;
        command_position = strtok(NULL, delimiters);
    }
    command = reverse_cmd(command);
    return command;
}
