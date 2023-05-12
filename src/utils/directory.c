/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** directory.c
*/

#include "mysh.h"
#include <dirent.h>
#include <stdlib.h>

char** get_files(char *path)
{
    DIR *dir = opendir(path);
    struct dirent *dirent;
    char **files = NULL;
    int i = 0;

    if (dir == NULL)
        return (NULL);
    while ((dirent = readdir(dir)) != NULL) {
        if (dirent->d_name[0] != '.') {
            files = realloc(files, sizeof(char *) * (i + 2));
            files[i] = strdup(dirent->d_name);
            i++;
        }
    }
    files[i] = NULL;
    closedir(dir);
    return (files);
}

int is_directory(char *path)
{
    DIR *dir = opendir(path);
    if (dir == NULL)
        return (0);
    closedir(dir);
    return (1);
}

void get_directory_files(char *path, char **files, int i, struct dirent *dirent)
{
    if (is_directory(path)) {
        files = realloc(files, sizeof(char *) * (i + 2));
        files[i] = strdup(dirent->d_name);
        i++;
    }
}

char** get_recursive_files(char* root)
{
    DIR *dir = opendir(root);
    struct dirent *dirent;
    char **files = NULL;
    char *path = NULL;
    int i = 0;

    if (dir == NULL)
        return (NULL);
    while ((dirent = readdir(dir)) != NULL) {
        if (dirent->d_name[0] != '.') {
            path = my_strcat(root, dirent->d_name);
            get_directory_files(path, files, i, dirent);
        }
    }
    files[i] = NULL;
    closedir(dir);
    return (files);
}
