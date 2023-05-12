/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** globbing.h
*/

#ifndef SH_42_GLOBBING_H
    #define SH_42_GLOBBING_H

        typedef enum {
            GLOB_STAR,
            GLOB_QUESTION,
            GLOB_BRACKET,
            GLOB_FILTER,
            GLOB_LITTERAL,
        } globber_type;

        typedef struct globber {
            char value[512];
            globber_type type;
            struct globber *next;
        } globber_t;

        globber_type get_globber(char *str);
        globber_t* reverse_globber(globber_t *globber);
        globber_t* globber_create(char* str);
        void dump_globber(globber_t* globber);
        void dump_globbing(globber_t *globber);
        int check_litteral(char** str, globber_t* globbing);
        int check_star(char** str, globber_t* globbing);
        int check_question(char** str, globber_t* globbing);
        int check_bracket(char** str, globber_t* globbing);
        int check_filter(char** str, globber_t* globbing);

#endif //SH_42_GLOBBING_H
