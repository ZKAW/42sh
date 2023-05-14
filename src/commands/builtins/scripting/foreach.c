/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** foreach.c
*/

#include "mysh.h"
#include "parsing.h"

static int handle_foreach_errors(BUILTIN_PARAMS)
{
    if (!is_alpha(cmd->foreach->var_name[0])) {
        throw_error("foreach: Variable name must begin with a letter.\n",
        shell, BUILTIN_ERROR);
        return (1);
    }
    return (0);
}

static void exec_foreach_cmds(BUILTIN_PARAMS)
{
    for (int i = 0; cmd->foreach->values[i]; i++) {
        set_var(shell, cmd->foreach->var_name, cmd->foreach->values[i]);
        handle_command(parse_command(cmd->foreach->cmd, shell), shell);
    }
    unset_var(shell, cmd->foreach->var_name);
}

static void prompt_foreach_args(BUILTIN_PARAMS)
{
    char* line = "";
    ssize_t size = 0; size_t i = 0;
    cmd->foreach->cmd = malloc(sizeof(char) * 1);
    cmd->foreach->cmd[0] = '\0';
    while (1) {
        my_putstr("foreach? ", 1);
        size = my_getline(&line, shell);
        if (size == 1) continue;
        if (size == EOF) break;
        line[size - 1] = '\0';
        if (!strcmp(clean_str(line), "end")) break;
        char *tmp = malloc(sizeof(char) *
                    (strlen(cmd->foreach->cmd) + size + 2));
        strcpy(tmp, cmd->foreach->cmd);
        strcat(tmp, line);
        strcat(tmp, ";");
        cmd->foreach->cmd = tmp;
        i++;
    }
    exec_foreach_cmds(cmd, shell);
}

void builtin_foreach(BUILTIN_PARAMS)
{
    if (handle_foreach_errors(cmd, shell)) return;
    size_t new_size = tablen(cmd->foreach->values) + 1;
    cmd->argv = realloc(cmd->argv, sizeof(char *) * new_size);
    cmd->arg_type = calloc(new_size, sizeof(int));
    arraydup(cmd->argv, cmd->foreach->values);
    check_globbing(cmd, shell);
    arraydup(cmd->foreach->values, cmd->argv);
    prompt_foreach_args(cmd, shell);
}
