/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** foreach.h
*/

#ifndef __FOREACH_H__
    #define __FOREACH_H__

typedef struct foreach {
    char var_name[256];
    char **values;
    char *cmd;
} foreach_t;

#endif //__FOREACH_H__
