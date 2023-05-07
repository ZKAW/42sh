/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin
*/

#ifndef BUILTIN_H_
    #define BUILTIN_H_

    #include "mysh.h"

void builtin_cd(char** cmd, shell_t* shell);
void builtin_env(char** cmd UNUSED, shell_t* shell);
void builtin_setenv(char** cmd, shell_t* shell);
void builtin_unsetenv(char** cmd, shell_t* shell);
void builtin_exit(char** cmd, shell_t* shell);

struct builtin_cmd {
    const char *name;
    void (*func)(char** cmd, shell_t* shell);
};

static const struct builtin_cmd builtin_cmds[] = {
    {"cd", builtin_cd},
    {"env", builtin_env},
    {"setenv", builtin_setenv},
    {"unsetenv", builtin_unsetenv},
    {"exit", builtin_exit},
    {NULL, NULL}
};

#endif /* !BUILTIN_H_ */
