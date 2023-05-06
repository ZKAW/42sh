/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin
*/

#ifndef BUILTIN_H_
    #define BUILTIN_H_

typedef struct alias_s {
    char *alias;
    char *command;
    struct alias_s *next;
} alias_t;

#endif /* !BUILTIN_H_ */
