/*
** EPITECH PROJECT, 2023
** where.c
** File description:
** aa
*/

#include "../../../include/mysh.h"

int disp_builtin(char **builtin, char *filename)
{
    for (int i = 0; builtin[i]; ++i)
        if (!strcmp(builtin[i], filename)) {
            my_putstr(builtin[i], 1);
            my_putstr(" is a shell built-in\n", 1);
            return 1;
        }
    return 0;
}

int disp_path(char *path, char *filename)
{
    char *tmp = NULL;
    int flag = 0;

    tmp = strcpy((tmp = malloc(sizeof(char) * (strlen(path) + 1))), path);
    if (access((tmp = concat_str(tmp, filename)), F_OK) != -1) {
        my_putstr(tmp, 1);
        my_putstr("\n", 1);
    } else
        ++flag;
    free(tmp);
    return flag;
}

int iterate_path(char **arr, char **argv, int i, int *flag)
{
    for (int j = 0; arr[j]; ++j)
        if (disp_path(arr[j], argv[i]) == 1)
            ++(*flag);
    return 0;
}

int check_dir(char **argv, char **arr)
{
    int flag = 0;
    int ret = 0;
    int ret_builtin = 0;
    char *builtin_cmd[10] = {"cd", "echo", "exit", "setenv", "unsetenv",
    "which", "where", "repeat", "history"};

    for (int i = 1; argv[i]; ++i) {
        ret_builtin = disp_builtin(builtin_cmd, argv[i]);
        iterate_path(arr, argv, i, &flag);
        if (flag == arrlen(arr) && !ret_builtin)
            ret = 1;
        flag = 0;
    }
    return ret;
}

void builtin_where(BUILTIN_PARAMS)
{
    int argc = arrlen(cmd->argv);
    char **arr = NULL;

    if (strcmp(cmd->argv[0], "where"))
        return;
    if (argc == 1) {
        my_putstr("where: Too few arguments.\n", 1);
        return;
    }
    arr = split_cmd(shell->envp);
    check_dir(cmd->argv, arr);
    free_arr(arr);
    return;
}
