/*
** EPITECH PROJECT, 2023
** repeat.c
** File description:
** aa
*/

#include "../../../include/mysh.h"

static int full_arrlen(char **arr)
{
    int total = 0;
    int i;

    for (i = 0; arr[i]; ++i)
        total += strlen(arr[i]);
    return total + i;
}

static int check_alph(char *str)
{
    for (int i = 0; str[i]; ++i)
        if (str[i] < 48 || str[i] > 57)
            return 1;
    return 0;
}

static char *concat_arr(char **arr, char delim)
{
    int len = 0;
    int str_index = 0;
    int total_len = full_arrlen(arr);
    char *str = calloc(total_len + 1, sizeof(char));

    if (!str)
        exit(84);
    for (int i = 0; arr[i]; ++i) {
        if (i > 0)
            str[str_index++] = delim;
        len = strlen(arr[i]);
        if (str_index + len >= total_len)
            exit(84);
        strcpy(str + str_index, arr[i]);
        str_index += len;
    }
    return str;
}

void repeat_builtin(char **cmd, shell_t *shell)
{
    char *str = NULL;
    list_t *list = NULL;
    if (strcmp(cmd[0], "repeat"))
        return;
    if (arrlen(cmd) < 3) {
        throw_error("repeat: Too few arguments.\n", shell, 1);
        return;
    }
    if (check_alph(cmd[1])) {
        throw_error("repeat: Badly formed number.\n", shell, 1);
        return;
    }
    str = concat_arr(cmd + 2, ' ');
    list = parse_command(str, shell);
    for (int i = atoi(cmd[1]); i != 0; --i)
        handle_command(list, shell);
    free(str);
    return;
}
