/*
** EPITECH PROJECT, 2022
** my_compute_square_root.c
** File description:
** task05
*/

int my_compute_square_root (int nb)
{
    if (nb <= 0 || nb == 1) {
        return 0;
    }
    for (int i = 0; i < nb; i++) {
        if (i * i == nb)
            return i;
    }
    return 0;
}
