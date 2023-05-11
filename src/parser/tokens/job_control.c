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
    cmd->job = init_job(shell, cmd->argv[0], BG);
    if (strlen(cmd_str) <= 1)
        return cmd_str;
    close_cmd((*command_array)->cmd);
    *command_array = append_list(*command_array);
    append_command(*command_array);
    return cmd_str;
}
