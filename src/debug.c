/*
** EPITECH PROJECT, 2022
** mini-shell2
** File description:
** debug.c
*/

#include "mysh.h"

void dump_args(char** argv)
{
    if (!argv[1])
        printf("no args");
    else
        printf("args: ");
    for (int i = 1; argv[i]; i++)
        printf("%s ", argv[i]);
    printf("\n");
}

void dump_cmd(cmd_t* cmd)
{
    while (cmd) {
        printf("path: %s\n", cmd->path);
        dump_args(cmd->argv);
        printf("pipe to next: %s\n",
            cmd->output_type == PIPE ? "yes" : "no");
        printf("redirect: %s\n", cmd->output ? cmd->output : "no");
        if (cmd->output) {
            printf("%s\n", cmd->append == O_APPEND ?
            "apend to file" : "overwrite text");
        }
        if (cmd->input) {
            printf("take %s as input\n", cmd->input);
        }
        cmd = cmd->next;
    }
}
