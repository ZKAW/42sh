/*
** EPITECH PROJECT, 2022
** mini-shell1
** File description:
** cd.c
*/

#include "mysh.h"

static void handle_cd_error(char* dir, shell_t* shell)
{
    char* error = strerror(errno);
    dprintf(2, "%s: %s.\n", dir, error);
    shell->state = BUILTIN_ERROR;
    set_status(shell, shell->state);
}

static void exec_cwdcmd(shell_t* shell)
{
    if (shell->cwdcmd != NULL) {
        list_t *list_cwdcmd = parse_command(shell->cwdcmd, shell);
        handle_command(list_cwdcmd, shell);
    }
}

static void change_dir(char *path, shell_t *shell)
{
    if (chdir(path) < 0) {
        handle_cd_error(path, shell);
        return;
    }
    set_status(shell, 0);
    exec_cwdcmd(shell);
}

static char *get_path(cmd_t *cmd, shell_t *shell, char *old_pwd)
{
    char *path = cmd->argv[1];

    if (cmd->argv[1] == NULL || is_whitespace(cmd->argv[1])
        || strcmp(cmd->argv[1], "~") == 0) {
        path = get_env_var(shell->envp, "HOME");
    } else if (strcmp(path, "-") == 0) {
        path = old_pwd;
    }

    return path;
}

void builtin_cd(BUILTIN_PARAMS)
{
    static char *old_pwd = NULL;

    if (tablen(cmd->argv) > 2) {
        throw_error("cd: Too many arguments.\n", shell, BUILTIN_ERROR);
        return;
    }
    if (old_pwd == NULL) old_pwd = strdup("");
    char *path = get_path(cmd, shell, old_pwd);
    old_pwd = getcwd(NULL, 0);
    change_dir(path, shell);
}
