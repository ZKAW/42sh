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
void repeat_builtin(BUILTIN_PARAMS);
void which_builtin(BUILTIN_PARAMS);
void where_builtin(BUILTIN_PARAMS);
void echo_builtin(BUILTIN_PARAMS);
void builtin_alias(BUILTIN_PARAMS);
void builtin_unalias(BUILTIN_PARAMS);

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
    {"repeat", repeat_builtin},
    {"which", which_builtin},
    {"where", where_builtin},
    {"echo", echo_builtin},
    {"alias", builtin_alias},
    {"unalias", builtin_unalias},
    {"jobs", builtin_jobs},
    {NULL, NULL}
};

#endif /* !BUILTIN_H_ */
