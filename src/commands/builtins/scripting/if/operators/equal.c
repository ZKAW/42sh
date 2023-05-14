/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** equal
*/

#include "mysh.h"

bool if_equal(IF_PARAMS)
{
    if (is_number(str1) && is_number(str2)) {
        return (atoi(str1) == atoi(str2));
    }
    return (false);
}

bool if_not_equal(IF_PARAMS)
{
    if (is_number(str1) && is_number(str2))
        return (atoi(str1) != atoi(str2));
    return (false);
}
