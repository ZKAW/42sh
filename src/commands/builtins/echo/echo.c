/*
** EPITECH PROJECT, 2023
** echo.c
** File description:
** aa
*/

#include "mysh.h"

static bool check_arg(char *str)
{
    int len = 0;

    if (str[0] == '-' && str[1] == 'n') {
        len = strlen(str);
        memmove(str, str + 3, len - 2);
        str[len - 3] = '\0';
        return true;
    }
    return false;
}

static bool parse_string(cmd_t *cmd)
{
    for (int i = 0; cmd->argv[i]; i++)
        if (cmd->arg_type[i] == QUOTTED)
            return true;
    return false;
}

static int check_interpreter(char *str, int *i, int *ret, bool has_pa)
{
    if (has_pa && str[*i] == '\\' && str[*i + 1] != '\0') {
        *ret = interpreter(str, *i);
        if (*ret == -1)
            return 2;
        *i += *ret;
        return 1;
    }
    return 0;
}

static int core_echo(char *str, cmd_t *cmd)
{
    bool is_arg = check_arg(str);
    bool has_pa = parse_string(cmd);
    int ret = 0;
    int retb = 0;

    for (int i = 0; str[i]; ++i) {
        retb = check_interpreter(str, &i, &ret, has_pa);
        if (retb == 2)
            break;
        if (retb == 1)
            continue;
        if (!has_pa && str[i] == '\\' && str[i + 1] != '\\')
            continue;
        putchar(str[i]);
    }
    if (!is_arg)
        putchar('\n');
    return 0;
}

void builtin_echo(BUILTIN_PARAMS)
{
    char *str = arr_to_str(cmd->argv, ' ');

    if (!strncmp(str, "echo", 4))
        core_echo(str + 5, cmd);
    SHARED_STATUS = 0;
    return;
}
