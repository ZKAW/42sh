/*
** EPITECH PROJECT, 2023
** path.c
** File description:
** aa
*/

#include "../../include/mysh.h"

extern int remove_first_n_chars(char *str, int n)
{
    int len = strlen(str);

    if (n > len)
        return 1;
    memmove(str, str + n, len - n + 1);
    return 0;
}

extern char **split_cmd(char **envp)
{
    char **arr = NULL;

    for (int i = 0; envp[i]; ++i) {
        if (!strncmp(envp[i], "PATH=", 5)) {
            arr = my_str_to_word_array(envp[i], ':');
            remove_first_n_chars(arr[0], 5);
            break;
        }
    }
    return arr;
}
