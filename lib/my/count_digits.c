/*
** EPITECH PROJECT, 2022
** my_printf
** File description:
** count_digits.c
*/

int count_digits(int nb)
{
    if (nb < 0) {
        nb = nb * -1;
    }
    int i = 1;
    for (i; nb > 9; i++) {
        nb = nb / 10;
    }
    return i;
}

int count_long_digits(long nb)
{
    if (nb < 0) {
        nb = nb * -1;
    }
    int i = 1;
    for (i; nb > 9; i++) {
        nb = nb / 10;
    }
    return i;
}
