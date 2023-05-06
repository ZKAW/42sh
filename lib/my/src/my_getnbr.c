/*
** EPITECH PROJECT, 2022
** my_getnbr.c
** File description:
** extract number from string
*/

int is_char_digit(char chr)
{
    if ((chr >= 48) && (chr <= 57)) {
        return (1);
    } else {
        return (0);
    }
}

int is_str_neg(char *str)
{
    for (int i = 0; str[i]; i++) {
        if ((str[i] == '-') && is_char_digit(str[i + 1])) {
            return (1);
        }
    }

    return (0);
}

int is_nbr_in_str(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (is_char_digit(str[i])) {
            return (1);
        }
    }

    return (0);
}

int my_getnbr(char *str)
{
    int nbr = 0;
    int sign = 1;

    if (is_str_neg(str)) {
        sign = -1;
    }
    for (int i = 0; str[i]; i++) {
        if (is_char_digit(str[i])) {
            nbr = nbr * 10 + str[i] - '0';
        }
    }

    return (nbr * sign);
}

int get_nbr_from(char *str, int i)
{
    int nbr = 0;
    int sign = 1;

    if (str[i] == '-') {
        sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        nbr = nbr * 10 + str[i] - '0';
        i++;
    }
    return (nbr * sign);
}
