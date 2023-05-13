/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** foreach.c
*/

#include "mysh.h"
#include "parsing.h"

void builtin_foreach(char** cmd, shell_t* shell)
{
    foreach_t* foreach; // le foreach est sensé etre stocké dans le cmd_t
    //relatif a la commande, faudra s'occuper de refactor les builtin pour 
    //qu'ils prennent un cmd_t en parametre plutot qu'un char** cmd
    (void)shell;
    (void)cmd;
    dprintf(2, "foreach: Command not implemented.\n");
}