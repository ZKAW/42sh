/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** memory
*/

#include "mysh.h"

void detach_shm(shared_memory_t shared_memory)
{
    shmdt(shared_memory.shmaddr);
    shmctl(shared_memory.shmid, IPC_RMID, NULL);
}
