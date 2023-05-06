/*
** EPITECH PROJECT, 2023
** myradar
** File description:
** tablen
*/

#include <unistd.h>

int tablen(char **tab)
{
    int i = 0;

    while (tab[i]) i++;
    return (i);
}
