/*
** EPITECH PROJECT, 2022
** my_putstr.c
** File description:
** task02
*/

int my_strlen(char const *str);

char   *my_revstr(char *str)
{
    char temp;
    int l = my_strlen(str) - 1;
    int i;
    for (i = 0; i < l; i++){
        temp = str[i];
        str[i] = str[l];
        str[l] = temp;
        l--;
    }
    return str;
}
