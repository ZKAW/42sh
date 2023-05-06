/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** my_str_to_word_array
*/

#include "lib.h"
#include <stdlib.h>

char **my_str_to_word_array(char *str, char delim)
{
    char **tab = malloc(sizeof(char *) * (my_strlen(str) + 2));
    int i = 0;
    int j = 0;
    int k = 0;

    while (str[i] != '\0') {
        if (str[i] == delim) {
            tab[j] = malloc(sizeof(char) * (i - k + 1));
            tab[j] = my_strncpy(tab[j], str + k, i - k);
            tab[j][i - k] = '\0';
            j++;
            k = i + 1;
        }
        i++;
    }
    tab[j] = malloc(sizeof(char) * (i - k + 1));
    tab[j] = my_strncpy(tab[j], str + k, i - k);
    tab[j][i - k] = '\0';
    tab[j + 1] = NULL;
    return (tab);
}
