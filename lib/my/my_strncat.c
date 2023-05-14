/*
** EPITECH PROJECT, 2022
** my_strncat.c
** File description:
** task03
*/

int my_strlen(char const *str);

char *my_strncat( char* dest , char* const src, int nb)
{
    int i;
    int size = my_strlen(dest);
    for (i = 0; i < nb && src[i] != '\0'; i++) {
        dest[size + i] = src[i];
    }
    dest[size + i] = '\0';
    return dest;
}
