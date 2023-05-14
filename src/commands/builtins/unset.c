/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** unset
*/

#include "mysh.h"

int parse_var_line(char* tmp, char*** keys_ptr, char*** values_ptr);
char* ar_to_str(cmd_t* cmd);

void unset_all(shell_t *shell)
{
    var_t *tmp;
    if (shell->vars->key == NULL) {
        return;
    }
    for (tmp = shell->vars; tmp->next != NULL; tmp = tmp->next) {
        tmp->key = NULL;
        tmp->value = NULL;
    }
    tmp->key = NULL;
    tmp->value = NULL;
}

void builtin_unset(BUILTIN_PARAMS)
{
    if (cmd->argv[1] == NULL)
        return throw_error("var: Too few arguments.\n", shell, 1);

    int argc = 0;
    for (int i = 1; cmd->argv[i] != NULL; i++)
        argc++;

    if (argc == 1 && strcmp(cmd->argv[1], "*") == 0) {
        unset_all(shell);
        return;
    }

    for (int i = 1; cmd->argv[i] != NULL; i++) {
        if (cmd->argv[i][0] == '=')
            return;
        unset_var(shell, cmd->argv[i]);
    }
}
