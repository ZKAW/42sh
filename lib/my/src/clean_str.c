/*
** EPITECH PROJECT, 2023
** lemin
** File description:
** clean_str
*/

#include <lib.h>
#include <stdlib.h>
#include <string.h>

char *clean_str(char* str)
{
    if (str == NULL) return (NULL);
    int i = 0, j = 0;
    int len = strlen(str);

    while (is_c_space(str[i])) i++;

    for (; i < len; i++) {
        if (!is_c_space(str[i]) || (i > 0 && !is_c_space(str[i - 1]))) {
            str[j++] = str[i];
        }
    }

    if (j > 0 && is_c_space(str[j - 1])) j--;
    str[j] = '\0';
    for (i = 0; i < j; i++) if (str[i] == '\t') str[i] = ' ';

    return (str);
}
