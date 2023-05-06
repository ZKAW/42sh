/*
** EPITECH PROJECT, 2022
** get_int_len.c
** File description:
** get int length
*/

int my_intlen(int value)
{
    int len = value < 0 ? 1 : 0;

    if (value == 0)
        return (1);

    while (value) {
        len++;
        value = value / 10;
    }

    return len;
}
