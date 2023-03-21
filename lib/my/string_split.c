/*
** EPITECH PROJECT, 2022
** my_str_to_word_array.c
** File description:
** task04
*/

#include <stdlib.h>

char* my_strdup(const char* str);
char *my_strncpy(char *dest, char const *src, int n);
int is_alpha(char c);
int my_strlen(char const * str);

int count_words_sep(char const *str, char separator)
{
    int i;
    int count = 1;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == separator)
            count++;
    }
    return count;
}

char** split_string_rec(char const * str, char **table,
char separator, long position)
{
    int i;
    for (i = 0; str[i] != separator && str[i] != '\0'; i++);
    table[position] = malloc(sizeof(char) * (i + 1));
    if (( i > 0 && str[i - 1] != separator) && str[i] == separator) {
        my_strncpy(table[position], str, i);
        if (my_strlen(table[position]))
            position++;
    }
    if (str[i] == '\0') {
        if (i > 0 && str[i - 1] != separator)
            my_strncpy(table[position++], str, i);
        table[position] = 0;
        return table;
    }
    return split_string_rec(&str[i + 1], table, separator, position);
}

char** string_split(char const * str, char separator)
{
    char **table;
    int count = count_words_sep(str, separator);
    table = malloc(sizeof(char*) * (count + 1));
    return split_string_rec(str, table, separator, 0);
}
