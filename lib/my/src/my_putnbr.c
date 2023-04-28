/*
** EPITECH PROJECT, 2023
** lib
** File description:
** my_putnbr
*/

#include "lib.h"

int my_putnbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = nb * -1;
    }
    if (nb >= 10) {
        my_putnbr(nb / 10);
        my_putnbr(nb % 10);
    } else
        my_putchar(nb + 48);
    return (0);
}
