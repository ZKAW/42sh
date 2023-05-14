/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** path
*/

#include "mysh.h"

static char **get_paths(shell_t *shell)
{
    char **paths = NULL;
    char *path = get_env_var(shell->envp, "PATH");
    if ((path == NULL) || (strlen(path) < 1)) {
        return shell->paths;
    }
    if (my_strcmp(path, "/") == 0) return NULL;
    paths = tokenize_string(path, ":");
    return paths;
}

char* get_full_path(char* cmd, shell_t* shell)
{
    char **path_dirs = get_paths(shell);
    if (path_dirs == NULL) return cmd;
    char *abs_path = NULL;
    for (int i = 0; path_dirs[i] != NULL; i++) {
        if (path_dirs[i][strlen(path_dirs[i]) - 1] == '\n') {
            path_dirs[i][strlen(path_dirs[i]) - 1] = '\0';
        }
        abs_path = concat_path(path_dirs[i], cmd);
        if (access(abs_path, F_OK) != -1) {
            return (abs_path);
        }
        free(abs_path);
    }
    return cmd;
}
