/*
** EPITECH PROJECT, 2022
** mini-shell2
** File description:
** setenv.c
*/

#include <stddef.h>
#include "mysh.h"

int check_env_name(char* name)
{
    if ((name[0] > 'Z' || name[0] < 'A')
    && (name[0] > 'z' || name[0] < 'a')) {
        write(2, "setenv: Variable name must ", 27);
        write(2, "begin with a letter.\n", 21);
        return 1;
    }
    for (int i = 1; name[i] != '\0'; i++) {
        if ((name[i] >= 'A' && name[i] <= 'Z')
        || (name[i] >= 'a' && name[i] <= 'z')
        || (name[i] >= '0' && name[i] <= '9'))
            continue;
        else {
            write(2, "setenv: Variable name must ", 27);
            write(2, "contain alphanumeric characters.\n", 33);
            return 1;
        }
    }
    return 0;
}

char* get_var_name(char** cmd, shell_t* shell)
{
    char* env_n;
    if (tablen(cmd) < 2) {
        print_array(shell->envp);
        return NULL;
    }
    if (tablen(cmd) > 3) {
        throw_error("setenv: Too many arguments.\n", shell, BUILTIN_ERROR);
        return NULL;
    }
    env_n = cmd[1];
    if (check_env_name(env_n))
        return NULL;
    return env_n;
}

void builtin_setenv(BUILTIN_PARAMS)
{
    int i = 0, size = 0;
    char* new_env, **envp = shell->envp, *env_n;
    env_n = get_var_name(cmd->argv, shell);

    if (env_n == NULL)
        return;
    for (; envp[i] && strncmp(envp[i], env_n, strlen(env_n)); i++);
    if (envp[i])
        envp = array_remove(i, envp);
    size = strlen(cmd->argv[1]) + 1;
    size += tablen(cmd->argv) == 3 ? strlen(cmd->argv[2]) : 0;
    new_env = malloc(sizeof(char) * (size + 1));
    strcpy(new_env, cmd->argv[1]);
    strcat(new_env, "=");
    if (tablen(cmd->argv) == 3)
        strcat(new_env, cmd->argv[2]);
    shell->envp = array_append(envp, new_env);
}
