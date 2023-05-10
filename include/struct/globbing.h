/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** globbing.h
*/

#ifndef SH_42_GLOBBING_H
    #define SH_42_GLOBBING_H

        static char* oppeners = "*?[{";
        static char* closers = "*?]}";

        typedef enum {
            GLOB_STAR, // * -> any string
            GLOB_QUESTION, // ? -> any char
            GLOB_BRACKET, // [a-z] -> any char in range
            GLOB_FILTER, // {a,b,c} -> a, b, c are filters.
            GLOB_LITTERAL, // litteral string
        } globber_type;

        typedef struct globber {
            char value[512];
            globber_type type;
            struct globber *next;
        } globber_t;

        globber_type get_globber(char *str);
        globber_t* reverse_globber(globber_t *globber);
        void dump_globbing(globber_t *globber);

#endif //SH_42_GLOBBING_H
