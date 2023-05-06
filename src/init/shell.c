/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** shell
*/

#include "mysh.h"

shell_t* init_shell(char** envp)
{
    shell_t* shell = malloc(sizeof(shell_t));
    shell->root = malloc(sizeof(char) * 500);
    shell->root = getcwd(shell->root, 500);
    shell->envp = envp_cpy(envp);
    shell->last_path = malloc(sizeof (char) * 500);
    shell->state = 0;
    shell->paths = get_env_paths(envp);
    return shell;
}
