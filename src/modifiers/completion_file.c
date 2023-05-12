/*
** EPITECH PROJECT, 2023
** completion_file.c
** File description:
** aa
*/

#include "../../include/mysh.h"

static int is_binary(const char *path)
{
    struct stat sb;

    stat(path, &sb);
    return (S_ISREG(sb.st_mode) && (sb.st_mode & S_IXUSR)) ? 1 : 0;
}

static int if_in_str(char *str, char *need)
{
    return (str[0] == need[0] && !strncmp(str, need, strlen(need))) ? 1 : 0;
}

extern int cmp_sort(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

static int stock_bin(dir_t *dir, int *count, char *cmd, char ***output)
{
    while ((dir->entry = readdir(dir->dir)) != NULL) {
        if (is_binary(dir->entry->d_name) &&
        if_in_str(dir->entry->d_name, cmd) == 1) {
            (*output)[*count] = strcpy(malloc(strlen(dir->entry->d_name) + 1),
            dir->entry->d_name);
            (*count)++;
        }
    }
    return 0;
}

extern int core_completion(char *cmd, char **arr, char ***output)
{
    dir_t *dir = malloc(sizeof(dir_t));
    int count = 0;
    char cwd[getpagesize()];
    getcwd(cwd, sizeof(cwd));
    *output = malloc(sizeof(char*) * getpagesize());
    for (int i = 0; arr[i]; ++i) {
        if (!(dir->dir = opendir(arr[i])))
            continue;
        chdir(arr[i]);
        stock_bin(dir, &count, cmd, output);
        closedir(dir->dir);
    }
    chdir(cwd);
    free(dir);
    (*output)[count] = NULL;
    return count;
}
