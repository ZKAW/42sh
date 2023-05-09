/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** parsing.c
*/

#include "mysh.h"

globber_type get_globber(char *str)
{
    for (int i = 0; oppeners[i]; i++)
        if (*str == oppeners[i]) return i;
    return GLOB_LITTERAL;
}

globber_t* parse_litteral(globber_t* globber, char** buffer)
{
    int i = 0;
    char* src = *buffer;
    while (*src && !strchr(oppeners, *src)
    && *src != ' ' && *src != '\t'
    && *src != '\n' && *src != '\0') {
        globber->value[i] = *src;
        i++;
        src++;
    }
    globber->value[i] = '\0';
    *buffer = src;
    return globber;
}

globber_t* get_next_globber(char **buffer)
{
    char* str = *buffer;
    globber_t *globber = malloc(sizeof(globber_t));
    globber->type = get_globber(str);
    int i = 0;
    if (globber->type == GLOB_LITTERAL) return parse_litteral(globber, buffer);
    else if (globber->type == GLOB_STAR || globber->type == GLOB_QUESTION) {
        *buffer = str + 1;
        return globber;
    }
    str++;
    while (*str && *str != closers[globber->type] && !strchr(oppeners, *str)
    && *str != ' ' && *str != '\t' && *str != '\n' && *str != '\0') {
        globber->value[i] = *str;
        i++;
        str++;
    }
    globber->value[i] = '\0';
    *buffer = str + 1;
    return globber;
}

globber_t* globber_create(char *str)
{
    globber_t *globber, *next = NULL;
    while (*str) {
        globber = get_next_globber(&str);
        globber->next = next;
        next = globber;
    }
    return globber;
}

globber_t* reverse_globber(globber_t *globber)
{
    globber_t *next = NULL, *tmp;
    while (globber) {
        tmp = globber->next;
        globber->next = next;
        next = globber;
        globber = tmp;
    }
    return next;
}

//globber_t *globber = globber_create(str);
//dump_globbing(reverse_globber(globber));
