/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** utils.c
*/

#include "mysh.h"
#include "struct/globbing.h"

int replace_globber(globber_t* globbing, int index, cmd_t* cmd);

void close_cmd(cmd_t* cmd)
{
    if (!cmd)
        return;
    if (cmd->argv) {
        cmd->argv[cmd->argc] = NULL;
        cmd->path = cmd->argv[0];
    } else {
        cmd->path = NULL;
    }
}

cmd_t* append_command(list_t* array)
{
    cmd_t* new_cmd = malloc(sizeof(cmd_t));
    if (array->cmd) {
        close_cmd(array->cmd);
        array->cmd->prev = new_cmd;
    }
    *new_cmd = (cmd_t){0};
    new_cmd->next = array->cmd;
    array->cmd = new_cmd;
    return new_cmd;
}

list_t* append_list(list_t* array)
{
    list_t* new_list = malloc(sizeof(list_t));
    *new_list = (list_t){0};
    if (array)
        array->prev = new_list;
    new_list->next = array;
    return new_list;
}
