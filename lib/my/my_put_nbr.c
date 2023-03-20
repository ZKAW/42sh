/*
** EPITECH PROJECT, 2022
** my_putnbr.c
** File description:
** task07
*/

void my_putchar(char c);

int my_put_nbr(int nb)
{
    int i = 0, ndigits = 0;
    int digits[100];
    if (nb < 0) {
        nb = nb * -1;
        my_putchar('-');
    }
    if ( nb == 0) {
        my_putchar('0');
        return 1;
    }
    for (i; nb != 0; i++) {
        digits[i] = nb % 10;
        nb = nb / 10;
    }
    ndigits = i;
    i--;
    for (i; i >= 0; i--) {
        my_putchar(digits[i] + '0');
    }
    return ndigits;
}
