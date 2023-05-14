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

void exit_detach_shm(shell_t* shell)
{
    int status = *shell->shared_status.shared_var;
    detach_shm(shell->shared_status);
    if (status == BUILTIN_ERROR)
        exit(1);
    exit(status);
}
