/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** foreach.c
*/

#include "mysh.h"
#include "parsing.h"

static int handle_foreach_errors(BUILTIN_PARAMS)
{
    if (!is_alpha(cmd->foreach->var_name[0])) {
        throw_error("foreach: Variable name must begin with a letter.\n",
        shell, 1);
        return (0);
    }
    if (tablen(cmd->argv) > 1) {
        throw_error("foreach: Too few arguments.\n", shell, 1);
        return (0);
    }
    return (0);
}

void builtin_foreach(BUILTIN_PARAMS)
{
    //relatif a la commande, faudra s'occuper de refactor les builtin pour
    //qu'ils prennent un cmd_t en parametre plutot qu'un char** cmd
    (void)shell;
    (void)cmd;
    if (handle_foreach_errors(cmd, shell)) return;

    printf("foreach->varname: %s\n", cmd->foreach->var_name);
    printf("foreach->cmd: %s\n", cmd->foreach->cmd);
    for (int i = 0; cmd->foreach->values[i]; i++) {
        printf("foreach->values[%d]: %s\n", i, cmd->foreach->values[i]);
    }
    printf("argc: %d\n", cmd->argc);
    for (int i = 0; cmd->argv[i]; i++) {
        printf("cmd->argv[%d]: %s\n", i, cmd->argv[i]);
    }
    // dprintf(2, "foreach: Command not implemented.\n");
}
