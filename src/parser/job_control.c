/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** job_control
*/

#include "mysh.h"

char *parse_bg(char *cmd_str, list_t **command_array, shell_t *shell)
{
    (void)shell;
    cmd_t *cmd = (*command_array)->cmd;
    cmd->is_background = true;
    cmd->job = init_job(shell, cmd->argv[0]);
    return cmd_str;
}
