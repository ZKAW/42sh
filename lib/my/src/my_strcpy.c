/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** my_strcpy
*/

char *my_strcpy(char *dest, char const *src)
{
    char *dest_start = dest;
    while (*src != '\0') {
        *dest++ = *src++;
    }
    *dest = '\0';
    return dest_start;
}
