/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** file
*/

#include "mysh.h"

int is_file(char *file_path)
{
    struct stat sb;
    if (stat(file_path, &sb) == -1) return 0;
    return S_ISREG(sb.st_mode);
}

int is_file_exist(char *file_path)
{
    struct stat sb;
    return stat(file_path, &sb) != -1;
}

int file_has_exec_rights(char *file_path)
{
    struct stat sb;
    if (stat(file_path, &sb) == -1) return 0;
    return (sb.st_mode & S_IXUSR) != 0;
}

char *concat_path(char *path, char *filename)
{
    char *abs_path = malloc(sizeof(char) *
                        (strlen(path) + strlen(filename) + 2));
    if (abs_path == NULL) return NULL;
    strcpy(abs_path, path);
    strcat(abs_path, "/");
    strcat(abs_path, filename);
    return abs_path;
}
