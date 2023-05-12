/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** concate_string
*/

#include "../../include/mysh.h"

extern char *concat_str(char *dest, char *src)
{
    int len_arr = strlen(dest);

    dest = realloc(dest, ((len_arr + strlen(src)) + 2));
    dest = (dest[len_arr - 1] != '/') ? strcat(dest, "/")
    : dest;
    return strcat(dest, src);
}
