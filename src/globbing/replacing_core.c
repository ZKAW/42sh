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

char** get_recursive_files(const char* root);

char* get_path_from_litteral(globber_t* globber)
{
    char new_path[4096] = {0};
    char* str = strdup(globber->value);
    char* start_ptr = str;
    while (strchr(str, '/')) str++;
    strncpy(new_path, globber->value, str - start_ptr);
    return strdup(new_path);
}

char* get_globbing_path(globber_t** globbing)
{
    globber_t* globber = *globbing;
    char path[4096] = {0};
    if (globber->type != GLOB_LITTERAL)
        return strdup("./");
    return get_path_from_litteral(globber);
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

char** get_matching_files(char** files, char* path, globber_t* globbing)
{
    char full_files[4096] = {0};
    char** matched = malloc(sizeof(char*) * (tablen(files) + 1));
    int position = 0;
    for (int i = 0; files[i]; i++)
        if (match(!strcmp(path, "./") ? &files[i][2] : files[i], globbing))
            matched[position++] = !strcmp(path, "./") ? &files[i][2] : files[i];
    matched[position] = NULL;
    return matched;
}

int replace_globber(globber_t* globbing, int index, cmd_t* cmd)
{
    shell_t* shell = get_shell(NULL);
    char* path = get_globbing_path(&globbing);
    char** files = get_recursive_files(path);
    if (files == NULL) {
        dprintf(2, "%s\n", strerror(errno));
        set_status(shell, 1);
        exit(1);
    }
    char** matched = get_matching_files(files, path, globbing);
    replace_arr_at_index(&cmd->argv, matched, index);
    if (tablen(matched) == 0) {
        dprintf(2, "%s: No match.\n", cmd->argv[0]);
        set_status(shell, 1);
        exit(1);
        return 0;
    }
    return tablen(matched) - 1;
}
