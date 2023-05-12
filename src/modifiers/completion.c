/*
** EPITECH PROJECT, 2023
** completion.c
** File description:
** completion
*/

#include "../../include/mysh.h"

static int sort_completion(char **strings)
{
    int j = 0;

    qsort(strings, arrlen(strings), sizeof(char *), cmp_sort);
    for (int i = 1; i < arrlen(strings); i++) {
        if (strcmp(strings[j], strings[i]) != 0) {
            j++;
            strings[j] = strings[i];
        }
    }
    strings[j + 1] = NULL;
    return j + 1;
}

static char *check_str(char *str, char *next_str)
{
    int len_a = strlen(str);
    int len_b = strlen(next_str);

    if (len_a < len_b)
        len_b -= len_a;
    for (int i = 0; i < len_b; ++i)
        my_putstr(" ", 1);
    return "\t";
}

static int print_sec_line(char **out)
{
    for (int i = 0; out[i]; ++i) {
        if (i == 0) {
            my_putstr(out[1], 1);
            my_putstr("\t", 1);
            continue;
        } if (i % 2 == 0) {
            my_putstr(out[i], 1);
            my_putstr((out[i + 1] == NULL ||
            out[i + 2] == NULL) ? "\n" : check_str(out[i - 1], out[i]), 1);
        }
    }
    return 0;
}

static int print_completion(char **out)
{
    for (int i = 0; out[i]; ++i) {
        if (i == 1) {
            my_putstr(out[0], 1);
            my_putstr("\t", 1);
            continue;
        } if (i % 2 != 0) {
            my_putstr(out[i], 1);
            my_putstr((out[i + 1] == NULL ||
            out[i + 2] == NULL) ? "\n" : check_str(out[i], out[i + 1]), 1);
        }
    }
    print_sec_line(out);
    return 0;
}

extern int completion(char *cmd, char **envp)
{
    char **arr = NULL;
    char **out = NULL;
    for (int i = 0; cmd[i]; ++i)
        if (cmd[i] == ' ')
            return 0;
    arr = split_cmd(envp);
    core_completion(cmd, arr, &out);
    sort_completion(out);
    print_completion(out);
    return 0;
}
