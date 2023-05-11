/*
** EPITECH PROJECT, 2022
** mini-shell1
** File description:
** main.c
*/

#include "mysh.h"

ssize_t my_getline(char **bufferptr, shell_t* shell);

void handle_command(list_t* list, shell_t* shell)
{
    cmd_t* head;
    if (list == NULL) {
        printf("Invalid null command.\n");
        shell->state = 1;
        SHARED_STATUS = shell->state;
    }
    while (list) {
        if ((list->condition == OR && shell->state == 0)
        || (list->condition == AND && shell->state != 0)) {
            list = list->next;
            continue;
        }
        head = list->cmd;
        if (is_builtin(head->path)) {
            run_builtin(head, shell);
        } else {
            execute(head, shell);
        }
        list = list->next;
    }
}

int verify_pipe(shell_t* shell)
{
    ssize_t size = 0;
    size_t len = 0;
    char* line = "";
    int status = 0;

    if (isatty(0))
        return 0;
    while (size != EOF) {
        size = getline(&line, &len, stdin);
        if (size == 1) continue;
        if (size == EOF) return 1;
        status = SHARED_STATUS;
        handle_command(parse_command(line, shell), shell);
        if (status == 1) {
            shell->state = status;
            return 1;
        }
    }
    return 1;
}

void exit_shm(shell_t* shell)
{
    int status = *shell->shared_status.shared_var;
    detach_shm(shell->shared_status);
    exit(status);
}

int main(int ac UNUSED, char** av UNUSED, char** envp)
{
    ssize_t size = 0;
    char* line = "";
    shell_t* shell = get_shell(init_shell(envp));
    if (verify_pipe(shell))
        exit_shm(shell);
    while (1) {
        my_putstr(get_prompt_prefix(), 1);
        size = my_getline(&line, shell);
        if (size == 1) continue;
        if (size == EOF) break;
        handle_command(parse_command(line, shell), shell);
    }
    if (isatty(0))
        write(1, "exit\n", 5);
    exit_shm(shell);
    return (shell->state);
}

// int main() {
//     pid_t pid = fork();

//     if (pid == 0) {
//         // Child process
//         printf("Child process executing...\n");
//         sleep(10); // Simulate some work
//         printf("Child process exiting...\n");
//         exit(0);
//     } else if (pid > 0) {
//         // Parent process
//         printf("Parent process executing...\n");
//         printf("Sending SIGSTOP signal to child process...\n");
//         kill(pid, SIGSTOP); // Suspend the child process
//         printf("Child process suspended\n");
//         sleep(5); // Wait for 5 seconds
//         printf("Sending SIGCONT signal to child process...\n");
//         kill(pid, SIGCONT); // Resume the child process
//         wait(NULL); // Wait for the child process to exit
//     } else {
//         // Error
//         printf("Failed to create child process\n");
//         return 1;
//     }

//     return 0;
// }
