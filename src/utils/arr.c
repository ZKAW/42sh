/*
** EPITECH PROJECT, 2023
** arr.c
** File description:
** aa
*/

#include "../../include/mysh.h"

extern char* arr_to_str(char** arr, char delim)
{
    char *result = NULL;
    int currentIndex = 0;
    int totalLength = 0;
    for (int i = 0; arr[i] != NULL; i++)
        totalLength += strlen(arr[i]) + 1;

    result = malloc(totalLength * sizeof(char));
    for (int i = 0; arr[i] != NULL; i++) {
        strcpy(result + currentIndex, arr[i]);
        currentIndex += strlen(arr[i]);
        result[currentIndex] = delim;
        currentIndex++;
    }
    result[currentIndex - 1] = '\0';
    return result;
}
