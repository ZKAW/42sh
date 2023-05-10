/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** replacing.c
*/

#include "mysh.h"
#include <alloca.h>
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
    if (!globbing->next)
        return 1;
    while (*cpy) {
        if (match(cpy, globbing->next)) {
            *str = cpy;
            return 1;
        }
        cpy++;
    }
    return 1;
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
    char* filter = globbing->value;
    int i = 0;

    while (filter[i]) {
        if (filter[i] == *cpy) {
            *str += 1;
            return 1;
        }
        i++;
    }
    return 0;
}

int replace_globber(globber_t* globbing, int index, cmd_t* cmd)
{
    char* matched[1000] = {NULL};
    int position = 0;
    char** files = get_files(".");
    for (int i = 0; files[i]; i++) {
        if (match(files[i], globbing))
            matched[position++] = files[i];
    }
    if (tablen(matched) == 0)
        return 0;
    replace_arr_at_index(&cmd->argv, matched, index);
    return tablen(matched) - 1;
}

int match(char* str, globber_t* globbing)
{
    char* head = str;
    int (*check[])(char**, globber_t*) = {check_star, check_question,
        check_bracket, check_filter, check_litteral};
    while (globbing) {
        if (!check[globbing->type](&str, globbing))
            return 0;
        globbing = globbing->next;
    }
    if (*str != '\0')
        return 1;
    return 1;
}


