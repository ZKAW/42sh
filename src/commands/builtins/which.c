/*
** EPITECH PROJECT, 2023
** which.c
** File description:
** aa
*/

#include "../../../include/mysh.h"

static char *concat_path_len(char *path, char *cmd, int len)
{
    char *str = NULL;

    str = malloc(sizeof(char) * (strlen(path) + len));
    str[0] = '\0';
    strcat(str, path);
    strcat(str, "/");
    strcat(str, cmd);
    return str;
}

static int check_builtin(char **builtin_cmd, char *cmd)
{
    for (int i = 0; builtin_cmd[i]; ++i)
        if (strcmp(builtin_cmd[i], cmd) == 0) {
            my_putstr(cmd, 1);
            my_putstr(": shell built-in command.\n", 1);
            return 1;
        }
    return 0;
}

static int which_core(char *cmd, char **arr)
{
    char *str = NULL;
    int len = strlen(cmd) + 2;
    char *builtin_cmd[10] = {"cd", "echo", "exit", "setenv", "unsetenv",
    "which", "where", "repeat", "history"};

    if (check_builtin(builtin_cmd, cmd))
        return 0;
    for (int i = 0; arr[i]; ++i) {
        if (access((str = concat_path_len(arr[i], cmd, len)), F_OK) != -1) {
            my_putstr(str, 1);
            my_putstr("\n", 1);
            free(str);
            return 0;
        }
        free(str);
    }
    my_putstr(cmd, 1);
    my_putstr(": Command not found.\n", 1);
    return 1;
}

void builtin_which(BUILTIN_PARAMS)
{
    char **arr = NULL;
    int argc = arrlen(cmd->argv);

    if (strcmp(cmd->argv[0], "which"))
        return;
    if (argc == 1) {
        my_putstr("which: Too few arguments.\n", 1);
        return;
    }
    arr = split_cmd(shell->envp);
    for (int i = 1; cmd->argv[i]; ++i)
        which_core(cmd->argv[i], arr);
    free_arr(arr);
    return;
}
