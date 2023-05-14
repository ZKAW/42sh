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
    while (list) {
        if ((list->condition == OR && SHARED_STATUS == 0)
        || (list->condition == AND && SHARED_STATUS != 0)) {
            list = list->next; continue;
        }
        head = list->cmd;
        if (!head) {
            list = list->next;
            continue;
        }
        if (!head->subshell && is_builtin(head->path)) run_builtin(head, shell);
        else
            execute(head, shell);
        list = list->next;
    }
    if (shell->precmd != NULL && shell->loop == 0) {
        list_t *list_precmd = parse_command(shell->precmd, shell);
        shell->loop = 1; handle_command(list_precmd, shell);
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
        handle_command(parse_command(line, shell), shell);
        if (SHARED_STATUS == BUILTIN_ERROR) {
            set_status(shell, 1);
            return 1;
        }
    }
    return 1;
}

void exit_shm(shell_t* shell)
{
    int status = *shell->shared_status.shared_var;
    detach_shm(shell->shared_status);
    if (status == BUILTIN_ERROR)
        exit(1);
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
        shell->loop = 0;
        handle_command(parse_command(line, shell), shell);
    }
    if (isatty(0)) write(1, "exit\n", 5);
    exit_shm(shell);
    if (shell->state == BUILTIN_ERROR)
        return (1);
    return (shell->state);
}
