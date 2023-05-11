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

        typedef struct string_s {
            char str[4096];
            char hour[6];
            int position;
            int len;
            struct string_s* prev;
            struct string_s* next;
        } string_t;

        typedef struct history {
            string_t* head;
            string_t* tail;
            string_t* current;
            int len;
            int position;
        } history_t;

            #define UP "\x1B[A"
            #define DOWN "\x1B[B"
            #define LEFT "\x1B[C"
            #define RIGHT "\x1B[D"
            #define DEL_CHAR "\b \b"

        string_t* create_string(void);
        void append_string(char c, string_t* string);
        void print_string(string_t* string);
        char* merge_string(string_t* string, shell_t* shell);
        void show_string_info(string_t* string);
        char* get_last_command(shell_t* shell);
#endif
