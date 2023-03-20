/*
** EPITECH PROJECT, 2022
** my_strcat.c
** File description:
** task02
*/

int my_strlen(char const *str);

void my_strcat(char* dest, char* const src)
{
    int i;
    int size = my_strlen(dest);
    for (i = 0; src[i] != '\0'; i++) {
        dest[size + i] = src[i];
    }
    dest[size + i] = '\0';
}
