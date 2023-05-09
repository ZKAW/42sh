/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** background
*/

#include "mysh.h"

char *parse_bg(char *cmd_str, list_t **command_array, shell_t *shell)
{
    (void)shell;
    cmd_t* cmd = (*command_array)->cmd;
    dprintf(2, "cmd_str: %s\n", cmd_str);
    for (int i = 0; cmd->argv[i]; i++) {
        dprintf(2, "cmd->argv[%d]: %s\n", i, cmd->argv[i]);
    }
    (*command_array)->is_background = true;
    return cmd_str;
}
