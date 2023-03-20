/*
** EPITECH PROJECT, 2022
** my_swap.c
** File description:
** task01
*/

void    my_swap(int *a, int *b)
{
    int temp = *b;
    *b = *a;
    *a = temp;
}
