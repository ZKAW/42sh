/*
** EPITECH PROJECT, 2023
** dir.h
** File description:
** aa
*/

#ifndef DIR_H
    #define DIR_H

    #include <dirent.h>

    typedef struct {
        DIR *dir;
        struct dirent *entry;
    }dir_t;
#endif
