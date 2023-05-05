/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** commands
*/

#include "mysh.h"

list_t* get_command(char * str)
{
    list_t* command_array = parse_command(str);
    command_array = reverse_cmd(command_array);
    return command_array;
}
