/*
** EPITECH PROJECT, 2022
** my_ls
** File description:
** is_alpha.c
*/

int is_alpha(char c)
{
    if (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z')
        return 1;
    else
        return 0;
}
