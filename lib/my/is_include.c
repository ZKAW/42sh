/*
** EPITECH PROJECT, 2022
** my_ls
** File description:
** is_include.c
*/

int is_include(char to_find, char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == to_find)
            return 1;
    }
    return 0;
}
