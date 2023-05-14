/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** shebang
*/

#include "mysh.h"

char *get_shebang(char *path)
{
    FILE *file = fopen(path, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t size = 0;

    if (file == NULL)
        return NULL;
    size = getline(&line, &len, file);
    if (size == -1)
        return NULL;
    if (strncmp(line, "#!", 2) != 0)
        return NULL;
    fclose(file);
    return line;
}

static int execve_shebang(char *path, char **argv, char **envp, char *shebang)
{
    char **arr = malloc(sizeof(char *) * 3);
    arr[0] = shebang;
    arr[1] = path;
    arr[2] = NULL;
    if (execve(get_env_var(envp, "SHELL"), arr, envp) == -1) {
        return -1;
    }
    return 0;
}

int my_execve(char* path, char **argv, char **envp)
{
    char *shebang = get_shebang(path);
    if (shebang == NULL)
        return execve(path, argv, envp);

    if (execve_shebang(path, argv, envp, shebang) == -1)
        return -1;

    return 0;
}
