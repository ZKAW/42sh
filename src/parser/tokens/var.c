/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** vars
*/

#include "mysh.h"
#include <string.h>

void close_cmd(cmd_t* cmd);
cmd_t* append_command(list_t* array);
list_t* append_list(list_t* array);
char* parse_file_name(char** cmd_str);
char* parse_var_name(char** cmd_str);

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

char* translate_min_on_maj(char* str)
{
    int i = 0;
    int len = strlen(str);
    char* new_str = malloc(sizeof(char) * (len + 1));

    for (; i < len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            new_str[i] = str[i] - 32;
        else
            new_str[i] = str[i];
    }
    new_str[i] = '\0';
    return new_str;
}

char* parse_var(char* cmd_str, list_t** command_array, shell_t* shell)
{
    if (*cmd_str == '\0' || *(cmd_str - 1) != '$') {
        add_arg(*command_array, strdup("$"), SIMPLE);
        return cmd_str;
    }
    cmd_t* cmd = (*command_array)->cmd;
    char* var_name = parse_var_name(&cmd_str);
    char *var = get_local_var(shell, var_name);
    if (var == NULL) var = get_env_var(shell->envp, var_name);
    if (var == NULL) {
        char* copy = strdup(translate_min_on_maj(var_name));
        var = get_env_var(shell->envp, copy);
    }
    if (var == NULL) {
        printf("%s: Undefined variable.", var_name);
        set_status(shell, 1);
        return cmd_str;
    }
    add_arg(*command_array, strdup(var), SIMPLE);
    return cmd_str;
}
