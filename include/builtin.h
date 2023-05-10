/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin
*/

#ifndef BUILTIN_H_
    #define BUILTIN_H_

    #include "mysh.h"

    #define BUILTIN_PARAMS char** cmd, shell_t* shell

void builtin_cd(BUILTIN_PARAMS);
void builtin_env(BUILTIN_PARAMS);
void builtin_setenv(BUILTIN_PARAMS);
void builtin_unsetenv(BUILTIN_PARAMS);
void builtin_exit(BUILTIN_PARAMS);
void builtin_jobs(BUILTIN_PARAMS);

struct builtin_cmd {
    const char *name;
    void (*func)(BUILTIN_PARAMS);
};

static const struct builtin_cmd builtin_cmds[] = {
    {"cd", builtin_cd},
    {"env", builtin_env},
    {"printenv", builtin_env},
    {"setenv", builtin_setenv},
    {"unsetenv", builtin_unsetenv},
    {"exit", builtin_exit},
    {"jobs", builtin_jobs},
    {NULL, NULL}
};

#endif /* !BUILTIN_H_ */
