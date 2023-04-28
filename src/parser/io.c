/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** io
*/

#include "mysh.h"

void parse_output(cmd_t* command)
{
    int append, overwrite;
    for (int i = 0; command->argv[i] != NULL; i++) {
        overwrite = strcmp(">", command->argv[i]);
        append = strcmp(">>", command->argv[i]);
        if (!overwrite || !append) {
            command->output_type = FILE_PATH;
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
    int file = 1, in = 1;
    for (int i = 0; command->argv[i] != NULL; i++) {
        file = strcmp("<", command->argv[i]);
        in = strcmp("<<", command->argv[i]);
        if (!file || !in) {
            command->input = command->argv[i + 1];
            command->argv = array_remove(i, command->argv);
            command->argv = array_remove(i, command->argv);
        }
        if (!in)
            command->input_type = STD;
        if (!file)
            command->input_type = FILE_PATH;
        if (!file || !in)
            break;
    }
    if (command->next && command->next->output_type == PIPE)
        command->input_type = PIPE;
}
