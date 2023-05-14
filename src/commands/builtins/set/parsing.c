/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** parsing.c
*/

#include "mysh.h"

char *skip_whitespace(char *str);

char* ar_to_str(cmd_t* cmd)
{
    char str[4096] = {0};
    char** argv = cmd->argv;
    int* type = cmd->arg_type;
    for (int i = 1; argv[i] != NULL; i++) {
        if (type[i] == QUOTTED) my_strcat(str, "\'");
        my_strcat(str, argv[i]);
        if (type[i] == QUOTTED) my_strcat(str, "\'");
        my_strcat(str, " ");
    }
    return strdup(str);
}

char* get_next_word(char* tmp, char* buffer, str_var_t* var)
{
    char quote = '\0';
    buffer[0] = '\0';
    if (*tmp == '\'' || *tmp == '"') {
        quote = *(tmp++);
        while (*tmp != quote && *tmp != '\0') {
            strncat(buffer, tmp, 1);
            tmp++;
        }
        tmp++;
    } else
        tmp = copy_until(buffer, tmp, " \t\n=");
    if (var->equal == 0) var->ws_before = is_c_space(*tmp);
    tmp = skip_whitespace(tmp);
    if (var->equal == 0) return tmp;
    if ((var->ws_after && var->ws_before)
    || (!var->ws_before && !var->ws_after)
    || (!var->ws_before && var->ws_after && quote == '\0'))
        return tmp;
    return NULL;
}

int check_equal(char** tmp, str_var_t* var)
{
    if (**tmp == '=') {
        var->equal++;
        (*tmp)++;
        if (is_c_space(**tmp)) {
            var->ws_after = 1;
            (*tmp) = skip_whitespace(*tmp);
        }
        return 1;
    }
    return 0;
}

char** append_var(char** array, char* var,int position)
{
    array = realloc(array, sizeof(char*) * (position + 2));
    array[position] = strdup(var);
    return array;
}

int parse_var_line(char* tmp, char*** keys_ptr, char*** values_ptr)
{
    str_var_t var = {0}; int position = 0, k_pos = 0, v_pos = 0;
    char buffer[4096] = {0}, **keys = *keys_ptr, **values = *values_ptr;
    while (*tmp != '\0' && *tmp) {
        if (check_equal(&tmp, &var)) continue;
        if (*tmp == '\0') break;
        tmp = get_next_word(tmp, buffer, &var);
        if (tmp == NULL) return NAME;
        if (var.equal == 0 && keys && k_pos < v_pos) {
            return START;
        }
        if (var.equal == 0) keys = append_var(keys, buffer, k_pos++);
        else {
            values = append_var(values, buffer, v_pos++);
            var = (str_var_t){0}; tmp = skip_whitespace(tmp);
        }
    }
    if (keys) keys[k_pos] = NULL;
    if (values) values[v_pos] = NULL;
    *keys_ptr = keys; *values_ptr = values;
    return ALL_GOOD;
}
