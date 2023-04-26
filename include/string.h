/*
** EPITECH PROJECT, 2022
** PSU
** File description:
** string.h
*/

#include <stdio.h>

#ifndef _STRING_H_
    #define _STRING_H_

        typedef struct shell shell_t;

        typedef struct char_s {
            char c;
            struct char_s* next;
            struct char_s* prev;
        } char_t;

        typedef struct string_s {
            char_t* first;
            char_t* last;
            char_t* before;
            char_t* after;
            char hour[6];
            struct string_s* next;
            struct string_s* prev;
        } string_t;

        string_t* create_string(shell_t* shell);
        char_t* append_string(char c, string_t* string);
        void print_string(string_t* string);
        char* merge_string(string_t* string);
        void show_string_info(string_t* string);
#endif
