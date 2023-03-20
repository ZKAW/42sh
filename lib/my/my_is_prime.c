/*
** EPITECH PROJECT, 2022
** my_is_prime.c
** File description:
** task06
*/

int my_is_prime(int nb)
{
    if (nb == 1 || nb <= 0)
        return 0;
    for (int i = 2; i < nb; i++) {
        if (nb % i == 0) {
            return 0;
        }
    }
    return 1;
}
