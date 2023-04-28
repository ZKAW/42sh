/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** commands
*/

#include "mysh.h"

cmd_t* parse_command(char* input, cmd_t* next)
{
    cmd_t* command = malloc(sizeof(cmd_t));
    command->argv = tokenize_string(input, " \t");
    command->path = command->argv[0];
    command->append = O_TRUNC;
    command->output = NULL;
    command->input = NULL;
    command->input_type = NONE;
    command->output_type = NONE;
    command->next = next;
    command->prev = NULL;
    if (command->next)
        command->next->prev = command;
    parse_output(command);
    parse_input(command);
    return command;
}

list_t* split_pipes(char* input, list_t* next)
{
    int i = 0;
    cmd_t* command = NULL;
    list_t* node = malloc(sizeof(list_t));
    char** parts = tokenize_string(input, "|");
    if ((tablen(parts) == 1 && CHAR_IN_STR('|', input))
    || parts[0] == NULL)
        return NULL;
    for (i = 0; parts[i + 1]; i++) {
        command = parse_command(parts[i], command);
        command->output_type = PIPE;
    }
    command = parse_command(parts[i], command);
    node->cmd = command;
    node->next = next;
    return node;
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
