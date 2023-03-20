/*
** EPITECH PROJECT, 2022
** my_strncpy.c
** File description:
** task02
*/

char* my_strncpy(char *dest, char const *src, int n)
{
    int i;
    for (i = 0; src[i] != '\0' && i < n; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}
