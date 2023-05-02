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
