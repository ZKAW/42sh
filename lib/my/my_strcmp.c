/*
** EPITECH PROJECT, 2022
** my_strcmp.c
** File description:
** task06
*/

int my_strcmp (char const * s1, char const * s2)
{
    int i;
    int result;
    for (i = 0; s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' ; i++);
    result = s1[i] - s2[i];
    return result;
}
