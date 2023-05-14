/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** directory.c
*/

#include "mysh.h"
#include <dirent.h>
#include <stdlib.h>

char** get_recursive_files(const char* root);

char* create_relative_path(const char* root, const char* name)
{
    size_t root_len = strlen(root);
    size_t name_len = strlen(name);
    size_t path_len = root_len + name_len + 2;
    char* path = malloc(path_len);
    if (path != NULL) {
        if (root[root_len - 1] == '/')
            snprintf(path, path_len, "%s%s", root, name);
        else
            snprintf(path, path_len, "%s/%s", root, name);
    }
    return path;
}

void add_subfiles(char* path, char*** files_ptr, int* position)
{
    int j = 0;
    int i = *position;
    char** files = *files_ptr;
    char** subfiles = get_recursive_files(path);
    while (subfiles[j] != NULL) {
        files = realloc(files, sizeof(char*) * (i + 2));
        files[i++] = subfiles[j++];
    }
    *files_ptr = files;
    *position = i;
    free(subfiles);
}

char** get_recursive_files(const char* root)
{
    DIR* dir = opendir(root);
    struct dirent* dirent;
    struct stat file_stat;
    char** files = NULL, *path = NULL, **subfiles;
    int i = 0, j;
    if (dir == NULL) return NULL;
    while ((dirent = readdir(dir)) != NULL) {
        if (!strncmp(dirent->d_name, ".", 1) || !strcmp(dirent->d_name, ".."))
            continue;
        path = create_relative_path(root, dirent->d_name);
        files = realloc(files, sizeof(char*) * (i + 2));
        files[i++] = strdup(path);
        if (stat(path, &file_stat) == 0 && S_ISDIR(file_stat.st_mode))
            add_subfiles(path, &files, &i);
        free(path);
    }
    files = realloc(files, sizeof(char*) * (i + 1));
    files[i] = NULL;
    closedir(dir);
    return files;
}
