/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** shell
*/

#include "mysh.h"

/*
typedef struct shared_memory_s {
    void *shared_var;
    char *shmaddr;
    int shmid;
} shared_memory_t;
*/

static void create_shared_status(shell_t* shell)
{
    shell->shared_status = create_shm(0);
}

shell_t* init_shell(char** envp)
{
    shell_t* shell = malloc(sizeof(shell_t));
    shell->root = malloc(sizeof(char) * 500);
    shell->root = getcwd(shell->root, 500);
    shell->envp = envp_cpy(envp);
    shell->last_path = malloc(sizeof (char) * 500);
    shell->state = 0;
    shell->paths = get_env_paths(envp);
        shell->history.head = NULL;
    shell->history.tail = NULL;
    shell->history.current = NULL;
    shell->history.position = 0;
    shell->history.len = 0;
    create_shared_status(shell);
    return shell;
}
