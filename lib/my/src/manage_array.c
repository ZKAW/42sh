/*
** EPITECH PROJECT, 2023
** lib
** File description:
** replace_arr
*/

#include "lib.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void replace_arr_at_index(char ***main_arr_ptr, char **sub_arr, int index)
{
    char **main_arr = *main_arr_ptr;
    int main_size = tablen(main_arr);
    int sub_size = tablen(sub_arr);
    size_t new_size = main_size + sub_size - 1;
    char **new_arr = malloc(sizeof(char *) * (new_size + 1 ));

    for (int i = 0; i < index; i++)
        new_arr[i] = main_arr[i];
    for (int i = 0; i < sub_size; i++)
        new_arr[index + i] = sub_arr[i];
    for (int i = index + 1; i < main_size; i++)
        new_arr[i + sub_size - 1] = main_arr[i];

    new_arr[new_size] = NULL;
    free(main_arr);
    *main_arr_ptr = new_arr;
}

void insert_arr_at_index(char ***main_arr_ptr, char **sub_arr, int index)
{
    char **main_arr = *main_arr_ptr;
    int main_size = tablen(main_arr);
    int sub_size = tablen(sub_arr);
    size_t new_size = main_size + sub_size;
    char **new_arr = malloc(sizeof(char *) * (new_size + 1 ));

    for (int i = 0; i < index; i++)
        new_arr[i] = main_arr[i];
    for (int i = 0; i < sub_size; i++)
        new_arr[index + i] = sub_arr[i];
    for (int i = index; i < main_size; i++)
        new_arr[i + sub_size] = main_arr[i];

    new_arr[new_size] = NULL;
    free(main_arr);
    *main_arr_ptr = new_arr;
}

char** array_append(char** array, char* const str)
{
    int old_lenght = tablen(array);
    char** new_arr = malloc(sizeof(char*) * (old_lenght + 2));
    for (int i = 0; array[i] != NULL; i++)
        new_arr[i] = malloc(sizeof(char) * (my_strlen(array[i]) + 1));
    arraydup(new_arr, array);
    new_arr[old_lenght] = strdup(str);
    new_arr[old_lenght + 1] = NULL;
    free_arr(array);
    return new_arr;
}

char** array_remove(int position, char** array)
{
    int i;
    char** new_array = malloc(sizeof(char*) * tablen(array));
    for (i = 0; i < position; i++)
        new_array[i] = array[i];
    for (i = position + 1; array[i]; i++)
        new_array[i - 1] = array[i];
    new_array[i - 1] = NULL;
    return new_array;
}
