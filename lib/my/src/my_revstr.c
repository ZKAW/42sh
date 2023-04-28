/*
** EPITECH PROJECT, 2022
** my_evil_str.c
** File description:
** reverse string
*/

int my_strlen(char const *str);

char *my_revstr(char *str)
{
    int i = 0;
    int len = my_strlen(str) - 1;
    char tmp_chr;

    while (i <= len / 2) {
        tmp_chr = str[i];
        str[i] = str[len - i];
        str[len - i] = tmp_chr;
        i++;
    }

    return str;
}
