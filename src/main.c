/*
** EPITECH PROJECT, 2022
** mini-shell1
** File description:
** main.c
*/

#include "mysh.h"

void print_path(void)
{
    char path[500];
    getcwd(path, 500);
    printf("%s $> ", path);
}

void handle_command(list_t* list, shell_t* shell)
{
    cmd_t* head;
    if (list == NULL) {
        printf("Invalid null command.\n");
        shell->state = 1;
    }
    while (list) {
        head = list->cmd;
        if (is_builtin(head->path))
            run_builtin(head, shell);
        if (is_builtin(head->path) && !head->next)
            return;
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
        handle_command(get_command(line), shell);
    }
    return 1;
}

int main(int ac UNUSED, char** av UNUSED, char** envp)
{
    size_t len = 0;
    ssize_t size = 0;
    char* line = "";
    shell_t* shell = init_shell(envp);

    if (verify_pipe(shell))
        return shell->state;
    while (1) {
        print_path();
        size = getline(&line, &len, stdin);
        if (size == 1) continue;
        if (size == EOF) break;
        handle_command(get_command(line), shell);
    }
    if (isatty(0))
        write(1, "exit\n", 5);

    return (shell->state);
}
