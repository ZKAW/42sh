/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** error
*/

#include <stdio.h>
#include <stdlib.h>

void error(char *msg)
{
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}
