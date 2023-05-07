/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** shared_memory
*/

#include "mysh.h"

shared_memory_t create_shm(int shared_var)
{
    shared_memory_t shared_memory;
    shared_memory.shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    if (shared_memory.shmid < 0)
        exit(84);
    shared_memory.shmaddr = shmat(shared_memory.shmid, NULL, 0);
    if (shared_memory.shmaddr == (char *) -1)
        exit(84);
    shared_memory.shared_var = (int *) shared_memory.shmaddr;
    *shared_memory.shared_var = shared_var;
    return shared_memory;
}
