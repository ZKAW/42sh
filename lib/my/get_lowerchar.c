/*
** EPITECH PROJECT, 2022
** my_ls
** File description:
** get_lowerchar.c
*/

char get_lowerchar(char c)
{
    if (c >= 'A' && c <= 'Z') {
        return c + 32;
    }
    return c;
}
