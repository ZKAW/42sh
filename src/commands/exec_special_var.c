/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** exec_special_var
*/

#include "mysh.h"

void precmd_on_alias(cmd_t* cmd, shell_t* shell)
{
    char *alias = NULL; alias_t *tmp = NULL;
    if (shell->aliases->alias == NULL)
        return;
    for (tmp = shell->aliases; tmp->next != NULL; tmp = tmp->next) {
        if (strcmp(tmp->alias, "precmd") == 0)
            alias = strdup(tmp->command);
    }
    if (strcmp(tmp->alias, "precmd") == 0)
        alias = strdup(tmp->command);

    if (alias != NULL) {
        char **argv_dup = malloc(sizeof(char*) * (tablen(cmd->argv) + 1));
        arraydup(argv_dup, cmd->argv);
        char** buffer = array_append(argv_dup, alias);
        for (int i = 0; buffer[i] != NULL; i++)
            cmd->argv[i] = buffer[i];
    }
}

char *get_local_var(shell_t *shell, char *key)
{
    if (shell->vars == NULL)
        return NULL;
    for (int i = 0; shell->vars->next != NULL; i++) {
        if (my_strcmp(shell->vars->key, key) == 0)
            return shell->vars->value;
        shell->vars = shell->vars->next;
    }
    if (my_strcmp(shell->vars->key, key) == 0)
        return shell->vars->value;
    return NULL;
}

// int assign_variables(cmd_t* cmd, shell_t* shell)
// {
//     // for (int i = 0; cmd->argv[i] != NULL; i++) {
//         // if (cmd->argv[i][0] == '$') {
//             char *var = get_local_var(shell, cmd->argv[i] + 1);
//             if (var == NULL) {
//                 printf("%s: Undefined variable.\n", cmd->argv[i] + 1);
//                 return 1;
//             }
//             printf("%s\n", var);
//             // cmd->argv[i] = var;
//         // }
//     // }
//     return 0;
// }

// int assign_variables(cmd_t* cmd, shell_t* shell)
// {
//     if (cmd->argv[0][0] == '$') {
//         char *var = get_local_var(shell, cmd->argv[0] + 1);
//         if (var == NULL) {
//             printf("%s: Undefined variable.\n", cmd->argv[0] + 1);
//             return 1;
//         }
//         cmd->argv[0] = var;
//     }
// }