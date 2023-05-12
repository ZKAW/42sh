/*
** EPITECH PROJECT, 2023
** echo_parsing.c
** File description:
** aa
*/

#include "../../../include/mysh.h"

extern int search_char(char *str, char c)
{
    int flag = 0;

    for (int i = 0; str[i]; ++i)
        if (str[i] == '\\' && str[i + 1] == c)
            ++flag;
    return flag;
}

extern int in_string(char *str, char c)
{
    for (int i = 0; str[i]; ++i)
        if (str[i] == c)
            return 1;
    return 0;
}

static int detect_args_n(args_t *struc, int i)
{
    if (!(struc->cmp1 = strcmp(struc->arg[i], "-n")) && !struc->f1) {
        struc->args[struc->j] = 'n';
        ++(struc->j);
        ++(struc->f1);
        return 1;
    } if (!(struc->cmp2 = strcmp(struc->arg[i], "-e")) && !struc->f2) {
        struc->args[struc->j] = 'e';
        ++(struc->j);
        ++(struc->f2);
        return 1;
    }
    if (!(struc->cmp3 = strcmp(struc->arg[i], "-E")) && !struc->f3) {
        struc->args[struc->j] = 'E';
        ++(struc->j);
        ++(struc->f3);
        return 1;
    }
    if (struc->cmp1 && struc->cmp2 && struc->cmp3)
        struc->tmp = strcat(strcat(struc->tmp, struc->arg[i]), " ");
    return 0;
}

extern char *parse_args(char **str, args_t *struc)
{
    struc->len = strlen(*str);
    struc->args = malloc(sizeof(char) * struc->len);
    struc->tmp = malloc(sizeof(char) * (struc->len + 2));
    struc->arg = my_str_to_word_array(*str, ' ');
    struc->j = 0;
    struc->f1 = 0, struc->f2 = 0, struc->f3 = 0;
    struc->cmp1 = 0, struc->cmp2 = 0, struc->cmp3 = 0;

    struc->tmp[0] = '\0';
    for (int i = 0; struc->arg[i]; ++i)
        if (detect_args_n(struc, i) == 1)
            continue;
    struc->args[struc->j] = '\0';
    struc->tmp[strlen(struc->tmp) - 1] = '\0';
    *str = struc->tmp;
    for (int i = 0; struc->arg[i]; ++i)
        free(struc->arg[i]);
    free(struc->arg);
    return struc->args;
}

extern char *parse_string(char *str)
{
    int len = strlen(str);
    char *res = malloc(sizeof(char) * (len + 1));

    strcpy(res, str);
    free(str);
    if (len > 1 && (res[0] == '\'' || res[0] == '\"') &&
    (res[len - 1] == '\'' || res[len - 1] == '\"')) {
        res[len - 1] = '\0';
        memmove(res, res + 1, len);
    }
    return res;
}
