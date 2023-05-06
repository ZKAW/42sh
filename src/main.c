/*
** EPITECH PROJECT, 2022
** mini-shell1
** File description:
** main.c
*/

#include "mysh.h"

void sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    my_putstr(get_prompt_prefix(), 1);
}

void handle_command(list_t* list, shell_t* shell)
{
    cmd_t* head;
    if (list == NULL) {
        printf("Invalid null command.\n");
        shell->state = 1;
    }
    while (list) {
        if ((list->condition == OR && shell->state == 0)
        || (list->condition == AND && shell->state != 0)) {
            list = list->next;
            continue;
        }
        head = list->cmd;
        if (is_builtin(head->path))
            run_builtin(head, shell);
        else
            execute(head, shell);
        list = list->next;
    }
}

int verify_pipe(shell_t* shell)
{
    ssize_t size = 0;
    size_t len = 0;
    char* line = "";

    if (isatty(0))
        return 0;
    while (size != EOF) {
        size = getline(&line, &len, stdin);
        if (size == 1)
            continue;
        if (size == EOF)
            return 1;
        handle_command(parse_command(line, shell), shell);
    }
    return 1;
}

int main(int ac UNUSED, char** av UNUSED, char** envp)
{
    size_t len = 0;
    ssize_t size = 0;
    char* line = "";
    shell_t* shell = init_shell(envp);
    call_env(shell->envp);
    signal(SIGINT, sigint_handler);

    if (verify_pipe(shell))
        return shell->state;
    while (1) {
        my_putstr(get_prompt_prefix(), 1);
        size = getline(&line, &len, stdin);
        if (size == 1) continue;
        if (size == EOF) break;
        handle_command(parse_command(line, shell), shell);
    }
    if (isatty(0))
        write(1, "exit\n", 5);

    return (shell->state);
}
