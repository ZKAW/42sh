/*
** EPITECH PROJECT, 2023
** echo_interpreter.c
** File description:
** aa
*/

#include "../../../../include/mysh.h"

static bool is_flag(char c)
{
    char *flags = "abcefnrtv";

    for (int i = 0; flags[i]; ++i)
        if (c == flags[i])
            return true;
    return false;
}

static int sub_interpreter(char *str, int i)
{
    if (str[i + 1] == 'n') {
        putchar('\n');
        return 1;
    } if (str[i + 1] == 't') {
        putchar('\t');
        return 1;
    } if (str[i + 1] == 'v') {
        putchar('\v');
        return 1;
    } if (str[i + 1] == 'a') {
        putchar('\a');
        return 1;
    } if (str[i + 1] == 'b') {
        putchar('\b');
        return 1;
    } if (str[i + 1] == 'f') {
        putchar('\f');
        return 1;
    }return 0;
}

extern int interpreter(char *str, int i)
{
    if (str[i + 1] == '0')
        return 1;
    if (str[i] == '\\' && !is_flag(str[i + 1])) {
        putchar('\\');
        return (str[i + 1] == '\\') ? 1 : 0;
    }
    if (sub_interpreter(str, i))
        return 1;
    if (str[i + 1] == 'r') {
        putchar('\r');
        return 1;
    }
    if (str[i + 1] == 'c')
        return -1;
    if (str[i + 1] == 'e') {
        putchar('\e');
        return 2;
    }
    return 0;
}
