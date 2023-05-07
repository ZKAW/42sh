/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** memory
*/

#ifndef MEMORY_H_
    #define MEMORY_H_

typedef struct shared_memory_s {
    int shmid;
    char *shmaddr;
    int *shared_var;
} shared_memory_t;

#endif /* !MEMORY_H_ */
