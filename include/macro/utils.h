/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** utils
*/

#ifndef MACRO_UTILS_H_
    #define MACRO_UTILS_H_

    #include <string.h>

    #define UNUSED __attribute__((unused))
    #define CHAR_IN_STR(c, str) (strchr(str, c) != NULL)


#endif /* !MACRO_UTILS_H_ */
