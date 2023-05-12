/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** vars
*/

#include "mysh.h"

void close_cmd(cmd_t* cmd);
cmd_t* append_command(list_t* array);
list_t* append_list(list_t* array);

int is_delim(char c, char* delims)
{
    for (int i = 0; delims[i] != '\0'; i++) {
        if (c == delims[i])
            return 1;
    }
    return 0;
}

char* get_next_token(char* cmd_str, char* delims)
{
    char* token = NULL;
    char* tmp = NULL;
    int i = 0;

    for (; cmd_str[i] != '\0'; i++) {
        if (is_delim(cmd_str[i], delims) == 0)
            break;
    }
    tmp = cmd_str + i;
    for (; cmd_str[i] != '\0'; i++) {
        if (is_delim(cmd_str[i], delims) == 1)
            break;
    }
    token = strndup(tmp, i);
    return token;
}

char* clear_str(char* str)
{
    int i = 0;
    int j = 0;
    int len = strlen(str);
    char* new_str = malloc(sizeof(char) * (len + 1));

    for (; i < len; i++) {
        if (str[i] == '\t' || str[i] == '\n' || str[i] == ' ')
            continue;
        new_str[j++] = str[i];
    }
    new_str[j] = '\0';
    return new_str;
}

char* parse_var(char* cmd_str, list_t** command_array, shell_t* shell)
{
    (void)shell;
    cmd_str = clear_str(cmd_str);

    cmd_t* cmd = (*command_array)->cmd;
    shell_t* saved_shell = get_shell(NULL);
    if (saved_shell == NULL) {
        return cmd_str;
    }
    char *var = get_local_var(saved_shell, cmd_str);
    if (var == NULL) {
        printf("%s: Undefined variable.\n", cmd_str);
        return cmd_str;
    }
    cmd_str = strdup(var);
    return cmd_str;
}
