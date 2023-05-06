/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** is_whitespace
*/

int is_whitespace(char *str)
{
    while (*str) {
        if (*str != ' ' && *str != '\t' && *str != '\n') return (0);
        str++;
    }
    return (1);
}

int is_c_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\n') return (1);
    return (0);
}
