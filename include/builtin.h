/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** builtin
*/

#ifndef BUILTIN_H_
    #define BUILTIN_H_

    #include "mysh.h"

    #define BUILTIN_PARAMS cmd_t *cmd, shell_t* shell

void builtin_cd(BUILTIN_PARAMS);
void builtin_env(BUILTIN_PARAMS);
void builtin_setenv(BUILTIN_PARAMS);
void builtin_unsetenv(BUILTIN_PARAMS);
void builtin_exit(BUILTIN_PARAMS);
void builtin_jobs(BUILTIN_PARAMS);
void builtin_repeat(BUILTIN_PARAMS);
void builtin_which(BUILTIN_PARAMS);
void builtin_where(BUILTIN_PARAMS);
void builtin_echo(BUILTIN_PARAMS);
void builtin_alias(BUILTIN_PARAMS);
void builtin_unalias(BUILTIN_PARAMS);
void builtin_set(BUILTIN_PARAMS);
void builtin_unset(BUILTIN_PARAMS);
void builtin_foreach(BUILTIN_PARAMS);
void builtin_if(BUILTIN_PARAMS);

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
    {"repeat", builtin_repeat},
    {"which", builtin_which},
    {"where", builtin_where},
    {"echo", builtin_echo},
    {"alias", builtin_alias},
    {"unalias", builtin_unalias},
    {"jobs", builtin_jobs},
    {"set", builtin_set},
    {"unset", builtin_unset},
    {"foreach", builtin_foreach},
    {"if", builtin_if},
    {NULL, NULL}
};

#endif /* !BUILTIN_H_ */
