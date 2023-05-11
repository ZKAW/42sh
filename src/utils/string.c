/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** string
*/

int have_space(char *str)
{
    int i = 0;
    for (; str[i] != '\0'; i++) {
        if (str[i] == ' ')
            return (1);
    }
    return (0);
}

int is_char_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

char *skip_whitespace(char *str)
{
    while (is_char_whitespace(*str))
        str++;
    return str;
}

char *skip_non_whitespace(char *str)
{
    while (*str && !is_char_whitespace(*str))
        str++;
    return str;
}
