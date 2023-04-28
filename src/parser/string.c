/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** input
*/

#include "mysh.h"

char **tokenize_string(char *input, char *sep)
{
    char *input_dup = my_strdup(input);
    char **parsed = malloc(sizeof(char *) * (my_strlen(input_dup) + 1));
    int i = 0;
    char *token = strtok(input_dup, sep);

    while (token != NULL) {
        parsed[i] = clean_str(my_strdup(token));
        token = strtok(NULL, sep);
        i++;
    }
    parsed[i] = NULL;
    return (parsed);
}
