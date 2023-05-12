/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** tokens.c
*/

#include "mysh.h"
#include "struct/globbing.h"

int match(char* str, globber_t* globbing);

int check_litteral(char** str, globber_t* globbing)
{
    if (!strncmp(*str, globbing->value, strlen(globbing->value))) {
        *str += strlen(globbing->value);
        return 1;
    }
    return 0;
}

int check_star(char** str, globber_t* globbing)
{
    char* cpy = *str;
    if (!globbing->next) {
        while (**str) {
            (*str)++;
        }
        return 1;
    }
    while (*cpy) {
        if (match(cpy, globbing->next)) {
            *str = cpy;
            return 1;
        }
        if (*cpy == '/' && globbing->next->type == GLOB_LITTERAL)
            return 0;
        cpy++;
    }
    return 0;
}

int check_question(char** str, globber_t* globbing)
{
    if (strlen(*str) > 0) {
        *str += 1;
        return 1;
    }
    return 0;
}

int check_bracket(char** str, globber_t* globbing)
{
    char start = globbing->value[0];
    char end = globbing->value[2];
    if (**str >= start && **str <= end) {
        *str += 1;
        return 1;
    }
    return 0;
}

int check_filter(char** str, globber_t* globbing)
{
    char* cpy = *str;
    char** filters = tokenize_string(globbing->value, ",");
    int i = 0;
    while (filters[i]) {
        if (my_strncmp(cpy, filters[i], strlen(filters[i])) == 0) {
            *str += strlen(filters[i]);
            return 1;
        }
        i++;
    }
    return 0;
}
