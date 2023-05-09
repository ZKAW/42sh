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
