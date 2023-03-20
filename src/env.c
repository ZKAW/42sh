/*
** EPITECH PROJECT, 2022
** mini-shell1
** File description:
** env.c
*/

#include <stdlib.h>
#include <unistd.h>
#include "../include/mini_shell.h"
#include "../include/my.h"

int check_env_name(char* name)
{
    for (int i = 0; name[i] != '\0'; i++) {
        if ((name[i] >= 'A' && name[i] <= 'Z')
        || (name[i] >= 'a' && name[i] <= 'z')
        || (name[i] >= '0' && name[i] <= '9'))
            continue;
        else {
            write(2, "setenv: Variable name must", 26);
            write(2, "contain alphanumeric characters.\n", 33);
            return 1;
        }
    }
    return 0;
}

void print_env(char** cmd, shell_t* shell)
{
    print_array(shell->envp);
}

char* get_var_name(char** cmd, shell_t* shell)
{
    char* env_n;
    if (my_arraylen(cmd) < 2) {
        print_array(shell->envp);
        return NULL;
    }
    if (my_arraylen(cmd) > 3) {
        write(2, "setenv: Too many arguments.\n", 29);
        return NULL;
    }
    env_n = cmd[1];
    if (check_env_name(env_n))
        return NULL;
    return env_n;
}

void my_setenv(char** cmd, shell_t* shell)
{
    int i = 0, size, var_s = 0;
    char* new_env, **envp = shell->envp, *env_n;
    env_n = get_var_name(cmd, shell);
    if (env_n == NULL)
        return;
    for (; envp[i] && my_strncmp(envp[i], env_n, my_strlen(env_n)); i++);
    if (envp[i])
        envp = array_remove(i, envp);
    size = my_strlen(cmd[1]) + 1;
    size += my_arraylen(cmd) == 3 ? my_strlen(cmd[2]) : 0;
    new_env = malloc(sizeof(char) * size + 1);
    my_strcpy(new_env, cmd[1]);
    my_strcat(new_env, "=");
    if (my_arraylen(cmd) == 3)
        my_strcat(new_env, cmd[2]);
    shell->envp = array_append(envp, new_env);
}

void my_unsetenv(char** cmd, shell_t* shell)
{
    char **envp = shell->envp, *name_var;
    if (my_arraylen(cmd) < 2) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        shell->state = 1;
        return;
    }
    name_var = cmd[1];
    for (int i = 0; envp[i]; i++) {
        if (!my_strncmp(envp[i], name_var, my_strlen(name_var))) {
            envp = array_remove(i, envp);
            break;
        }
    }
    shell->state = 0;
    shell->envp = envp;
}
