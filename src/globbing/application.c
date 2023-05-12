/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** application.c
*/

#include "mysh.h"
#include "struct/globbing.h"

int check_globbing(cmd_t* cmd, shell_t* shell)
{
    globber_t* globber = NULL;
    for (int i = 0; cmd->argv[i]; i++) {
        if (cmd->arg_type[i] != SIMPLE) continue;
        globber = globber_create(cmd->argv[i]);
        if (globber->type == GLOB_LITTERAL && !globber->next) continue;
        i = replace_globber(globber, i, cmd);
        if (i == 0) {
            SHARED_STATUS = 1;
            return 1;
        }
    }
    return 0;
}