/*
** EPITECH PROJECT, 2022
** myhunter
** File description:
** my_itoa
*/

#include "lib.h"
#include <stdlib.h>

char *my_itoa(int nbr)
{
    char *str = malloc(sizeof(char) * my_intlen(nbr) + 1);
    int i = 0;
    int is_negative = 0;

    if (nbr == 0) return ("0");
    if (nbr < 0) {
        is_negative = 1;
        nbr = -nbr;
    }
    str[my_intlen(nbr) + is_negative] = '\0';
    while (nbr > 0) {
        str[i] = nbr % 10 + '0';
        nbr /= 10;
        i++;
    }
    if (is_negative)
        str[i] = '-';
    return (my_revstr(str));
}

char *my_itoa_dest(char *dest, int nbr)
{
    int i = 0;
    int is_negative = 0;

    if (nbr == 0) return ("0");
    if (nbr < 0) {
        is_negative = 1;
        nbr = -nbr;
    }
    dest[my_intlen(nbr) + is_negative] = '\0';
    while (nbr > 0) {
        dest[i] = nbr % 10 + '0';
        nbr /= 10;
        i++;
    }
    if (is_negative)
        dest[i] = '-';
    return (my_revstr(dest));
}
