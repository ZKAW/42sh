/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** var
*/

#include "mysh.h"

char* array_to_str(char **cmd)
{
    char *tmp = malloc(sizeof(char) * 500);
    int i = 0;
    int j = 0;
    for (; cmd[i] != NULL; i++) {
        for (int k = 0; cmd[i][k] != '\0'; k++) {
            tmp[j] = cmd[i][k];
            j++;
        }
        tmp[j] = ' ';
        j++;
    }
    tmp[j] = '\0';
    return (tmp);
}

char* concatene_value(char **cmd)
{
    int len = 0;
    for (int i = 0; cmd[i] != NULL; i++) {
        len += strlen(cmd[i]);
    }
    char *tmp = malloc(sizeof(char) * (len + 1));
    int j = 0;
    for (int i = 0; cmd[i] != NULL; i++) {
        for (int k = 0; cmd[i][k] != '\0'; k++) {
            tmp[j] = cmd[i][k];
            j++;
        }
        tmp[j] = ' ';
        j++;
    }
    tmp[j] = '\0';
    return (tmp);
}
