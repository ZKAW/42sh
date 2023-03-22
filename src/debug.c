/*
** EPITECH PROJECT, 2022
** mini-shell2
** File description:
** debug.c
*/

#include <fcntl.h>
#include "../include/my.h"
#include "../include/mini_shell.h"

void dump_args(char** argv)
{
    if (!argv[1])
        my_printf("no args");
    else
        my_printf("args: ");
    for (int i = 1; argv[i]; i++)
        my_printf("%s ", argv[i]);
    my_putchar('\n');
}

void dump_cmd(cmd_t* cmd)
{
    while (cmd) {
        my_printf("path: %s\n", cmd->path);
        dump_args(cmd->argv);
        my_printf("pipe to next: %s\n",
            cmd->output_type == PIPE ? "yes" : "no");
        my_printf("redirect: %s\n", cmd->output ? cmd->output : "no");
        if (cmd->output) {
            my_printf("%s\n", cmd->append == O_APPEND ?
            "apend to file" : "overwrite text");
        }
        if (cmd->input) {
            my_printf("take %s as input\n", cmd->input);
        }
        cmd = cmd->next;
    }
}
