/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** dumps.c
*/

#include "mysh.h"

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

void dump_list(list_t* list)
{
    while (list) {
        dprintf(1, "\nNEW LIST:\n");
        dprintf(1, "condition: %d\n", list->condition);
        dump_cmd(list->cmd);
        list = list->next;
    }
}
