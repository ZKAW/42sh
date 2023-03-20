/*
** EPITECH PROJECT, 2022
** my_compute_power_rec.c
** File description:
** task03
*/

int    calc_power(int nb, int original, int it)
{
    if (it > 1)
        return calc_power(nb * original, original, it - 1);
    else
        return (nb);
}

int    my_compute_power_rec(int nb, int p)
{
    if (p == 0)
        return (1);
    else if (p < 0)
        return (0);
    else
        return calc_power(nb, nb, p);
}
