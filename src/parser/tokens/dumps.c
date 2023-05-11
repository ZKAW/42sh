/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** dumps.c
*/

#include "mysh.h"
#include "parsing.h"
#include "struct/globbing.h"

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

void dump_globber(globber_t* globber)
{
    if (globber->type == GLOB_LITTERAL)
        dprintf(1, "litteral string: %s", globber->value);
    if (globber->type == GLOB_STAR)
        dprintf(1, "any string");
    if (globber->type == GLOB_QUESTION)
        dprintf(1, "any char");
    if (globber->type == GLOB_BRACKET)
        dprintf(1, "any char in range %s", globber->value);
    if (globber->type == GLOB_FILTER)
        dprintf(1, "filter: %s", globber->value);
}

void dump_globbing(globber_t *globber)
{
    while (globber->next) {
        dump_globber(globber);
        globber = globber->next;
        dprintf(1, " -> ");
    }
    dump_globber(globber);
    dprintf(1, "\n");
}
