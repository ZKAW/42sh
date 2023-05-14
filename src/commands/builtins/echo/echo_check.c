/*
** EPITECH PROJECT, 2023
** echo_check.c
** File description:
** aa
*/

#include "mysh.h"

extern int print_help(void)
{
    my_putstr("Echo the STRING(s) to standard output.\n"
            "\t-n     do not output the trailing newline\n"
            "\t-e     enable interpretation of backslash escapes\n"
            "\t-E     disable interpretation of backslash escapes (default)\n"
            "\t--help  display this help and exit\n"
            "\t--version   output version information and exit\n", 1);
    return 0;
}

extern int check_interpretation(int *interpret, char *args)
{
    if (in_string(args, 'E') == 1)
        *interpret = 0;
    if (in_string(args, 'e') == 1)
        *interpret = 1;
    return 0;
}

extern int free_data(char *str, args_t *struc)
{
    free(str);
    free(struc->flag);
    free(struc->flag2);
    free(struc->args);
    free(struc);
    return 0;
}

extern int handle_basicdisplay(char *str, args_t *struc)
{
    if (struc->interpret == 0)
        my_putstr(str, 1);
    if (in_string(struc->args, 'n') == 0)
        my_putstr("\n", 1);
    return 0;
}

extern int check_back_backspaces(char *str, args_t *struc)
{
    for (int i = 0; str[i] && struc->interpret == 1; ++i) {
        if (str[i] == '\\' && str[i + 1] == 'b') {
            struc->flag[struc->b_flag] = i - 1;
            ++(struc->b_flag);
        }
        if (str[i] == '\\' && str[i + 1] == 'r') {
            struc->flag2[struc->r_flag] = i;
            ++(struc->r_flag);
        }
    }
    return 0;
}
