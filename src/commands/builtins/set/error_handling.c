/*
** EPITECH PROJECT, 2023
** error_handling.c
** File description:
** aa
*/

#include "mysh.h"

extern int error_handling_set(shell_t *shell, cmd_t *cmd)
{
    char **arr = cmd->argv;
    char **parsed = my_str_to_word_array(arr[1], '=');

    if (!is_alpha(parsed[0][0])) {
        throw_error("set: Variable name must begin with a letter.\n", shell, 1);
        return 1;
    }
    if (CHAR_IN_STR('?', parsed[1])) {
        throw_error("set: No match.\n", shell, 1);
        return 1;
    }
    if (!is_str_alphanum(parsed[0])) {
        throw_error("set: Variable name must contain alphanumeric characters.\n"
            , shell, 1);
        return 1;
    }
    return 0;
}
