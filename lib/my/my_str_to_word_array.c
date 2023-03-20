/*
** EPITECH PROJECT, 2022
** my_str_to_word_array.c
** File description:
** task04
*/

#include <stdlib.h>

char *my_strncpy(char *dest, char const *src, int n);
int is_alpha(char c);

int count_words(char const *str)
{
    int i;
    int count = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (!(is_alpha(str[i])) && is_alpha(str[ i- 1]))
            count++;
    }
    if (str[i] == '\0' && is_alpha(str[i - 1]))
        count++;
    return count;
}

char** word_to_array_rec(char const * str, char **table, int position)
{
    int i;
    for (i = 0; is_alpha(str[i]) && str[i] != '\0'; i++);
    table[position] = malloc(sizeof(char) * (i + 1));
    if (is_alpha(str[i - 1])) {
            my_strncpy(table[position], str, i);
            position++;
    }
    if (str[i] == '\0') {
        my_strncpy(table[position], str, i);
        table[position + 1] = 0;
        return table;
    }
    return word_to_array_rec(&str[i + 1], table, position);
}

char** my_str_to_word_array(char const * str)
{
    char **table;
    int count = count_words(str);
    table = malloc(sizeof(char*) * (count + 1));
    return word_to_array_rec(str, table, 0);
}
