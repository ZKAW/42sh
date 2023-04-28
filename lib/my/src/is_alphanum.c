/*
** EPITECH PROJECT, 2023
** lib
** File description:
** is_alphanum
*/

int is_alphanum(char c)
{
    if (c >= '0' && c <= '9') return (1);
    if (c >= 'a' && c <= 'z') return (1);
    if (c >= 'A' && c <= 'Z') return (1);
    if (c == '_') return (1);
    return (0);
}

int is_str_alphanum(char *str)
{
    while (*str) {
        if (!is_alphanum(*str)) return (0);
        str++;
    }
    return (1);
}
