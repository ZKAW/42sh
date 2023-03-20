/*
** EPITECH PROJECT, 2022
** my_strncmp.c
** File description:
** task07
*/

int my_strncmp (char const * s1, char const * s2, int n)
{
    int i;
    int result;
    for (i = 0; s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0'; i++) {
        if (i >= n - 1)
            break;
    }
    result = s1[i] - s2[i];
    return result;
}
