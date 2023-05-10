/*
** EPITECH PROJECT, 2023
** echo.c
** File description:
** aa
*/

#include "../../../include/mysh.h"

static int event_back_backspaces(args_t *struc, int *i)
{
    if (struc->r_flag > 0) {
        *i = struc->flag2[struc->j] + 1;
        --(struc->r_flag);
        ++(struc->j);
        return 1;
    }
    if (struc->b_flag > 0 && *i == struc->flag[struc->k]) {
        *i += 2;
        --(struc->b_flag);
        ++(struc->k);
        return 1;
    }
    return 0;
}

static int event_backspaces(char *str, int *i)
{
    if (str[*i] == '\\' && (str[*i + 1] == 'f' || str[*i + 1] == 'v')) {
        my_putstr("\n", 1);
        for (int j = 0; str[j] != '\\' && (str[j + 1] != 'f' ||
        str[j + 1] != 'v'); ++j)
            my_putstr(" ", 1);
        ++(*i);
        return 1;
    } if (str[*i] == '\\' && str[*i + 1] == 'n') {
        my_putstr("\n", 1);
        ++(*i);
        return 1;
    } if (str[*i] == '\\' && str[*i + 1] == 't') {
        my_putstr("\t", 1);
        ++(*i);
        return 1;
    } if (str[*i] == '\\' && str[*i + 1] == 'e') {
        *i += 2;
        return 1;
    }
    return 0;
}

static int check_backspaces(char *str, args_t *struc)
{
    struc->j = 0;
    for (int i = 0; str[i] && struc->interpret == 1; ++i) {
        if (event_back_backspaces(struc, &i) == 1)
            continue;
        if (event_backspaces(str, &i) == 1)
            continue;
        if (str[i] == '\\' && str[i + 1] == 'c')
            break;
        if (str[i] == '\\') {
            my_putstr("\\", 1);
            continue;
        }
        write(1, &str[i], 1);
    }
    return 0;
}

static int core_echo(char *str)
{
    args_t *struc = malloc(sizeof(args_t));
    struc->b_flag = 0, struc->r_flag = 0;
    struc->j = 0, struc->k = 0;
    struc->interpret = 0;
    struc->flag = malloc(sizeof(int) * search_char(str, 'b'));
    struc->flag2 = malloc(sizeof(int) * search_char(str, 'r'));
    struc->args = parse_args(&str, struc);

    str = parse_string(str);
    check_interpretation(&struc->interpret, struc->args);
    check_back_backspaces(str, struc);
    check_backspaces(str, struc);
    handle_basicdisplay(str, struc);
    return free_data(str, struc);
}

void echo_builtin(char **cmd, shell_t *shell)
{
    char *str = arr_to_str(cmd, ' ');

    if (!strcmp(str, "echo --help")) {
        print_help();
        return;
    }
    if (!strcmp(str, "echo --version")) {
        my_putstr("GNU coreutils 9.1\n", 1);
        return;
    }
    if (!strncmp(str, "echo", 4))
        core_echo(str + 5);
    return;
}
