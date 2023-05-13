/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** foreach.c
*/

#include "mysh.h"
#include "parsing.h"

void builtin_foreach(BUILTIN_PARAMS)
{
    //relatif a la commande, faudra s'occuper de refactor les builtin pour
    //qu'ils prennent un cmd_t en parametre plutot qu'un char** cmd
    (void)shell;
    (void)cmd;
    printf("foreach->cmd: %s\n", cmd->foreach->cmd);
    dprintf(2, "foreach: Command not implemented.\n");
}