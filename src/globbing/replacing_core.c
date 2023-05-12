/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** replacing.c
*/

#include "mysh.h"
#include <alloca.h>
#include <string.h>
#include "struct/globbing.h"

char* get_globbing_path(globber_t** globbing)
{
    globber_t* globber = *globbing;
    char path[4096] = {0};
    if (globber->type != GLOB_LITTERAL)
        return strdup("./");
    if (globber->value[0] == '/') {
        *globbing = globber->next;
        return strdup(globber->value);
    }
    strcat(path, "./");
    strcat(path, globber->value);
    *globbing = globber->next;
    return strdup(path);
}

int match(char* str, globber_t* globbing)
{
    char* head = str;
    int (*check[])(char**, globber_t*) = {check_star, check_question,
        check_bracket, check_filter, check_litteral};
    while (globbing) {
        if (!check[globbing->type](&str, globbing))
            return 0;
        globbing = globbing->next;
    }
    if (*str != '\0')
        return 0;
    return 1;
}

char* set_file_path(char* path, char* file)
{
    char full_path[4096] = {0};
    if (my_strncmp(path, "./", 2) == 0)
        strcat(full_path, path + 2);
    else
        strcat(full_path, path);
    strcat(full_path, file);
    return strdup(full_path);
}

char** get_matching_files(char** files, char* path, globber_t* globbing)
{
    char full_files[4096] = {0};
    char** matched = malloc(sizeof(char*) * (tablen(files) + 1));
    int position = 0;
    for (int i = 0; files[i]; i++)
        if (match(files[i], globbing))
            matched[position++] = set_file_path(path, files[i]);
    matched[position] = NULL;
    return matched;
}

int replace_globber(globber_t* globbing, int index, cmd_t* cmd)
{
    shell_t* shell = get_shell(NULL);
    char* path = get_globbing_path(&globbing);
    char** files = get_files(path);
    char** matched = get_matching_files(files, path, globbing);
    replace_arr_at_index(&cmd->argv, matched, index);
    if (tablen(matched) == 0) {
        dprintf(2, "%s: No match.\n", cmd->argv[0]);
        SHARED_STATUS = 1;
        return 0;
    }
    return tablen(matched) - 1;
}
