/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** comp
*/

#include "mysh.h"

bool if_greater(IF_PARAMS)
{
    if (is_number(str1) && is_number(str2))
        return (atoi(str1) > atoi(str2));
    return (false);
}

bool if_lower(IF_PARAMS)
{
    if (is_number(str1) && is_number(str2))
        return (atoi(str1) < atoi(str2));
    return (false);
}

bool if_greater_equal(IF_PARAMS)
{
    if (is_number(str1) && is_number(str2))
        return (atoi(str1) >= atoi(str2));
    return (false);
}

bool if_lower_equal(IF_PARAMS)
{
    if (is_number(str1) && is_number(str2))
        return (atoi(str1) <= atoi(str2));
    return (false);
}
