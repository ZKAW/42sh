/*
** EPITECH PROJECT, 2022
** mini-shell1
** File description:
** main.c
*/

#include "mysh.h"

void handle_command(list_t* list, shell_t* shell)
{
    cmd_t* head;
    if (shell->postcmd != NULL && shell->loop_postcmd == 0) postcmd(shell);
    while (list) {
        if ((list->condition == OR && SHARED_STATUS == 0)
        || (list->condition == AND && SHARED_STATUS != 0)) {
            list = list->next; continue;
        }
        head = list->cmd;
        if (!head) {
            list = list->next; continue;
        }
        if (!head->subshell && is_builtin(head->path)) run_builtin(head, shell);
        else
            execute(head, shell);
        list = list->next;
    }
    if (shell->precmd != NULL && shell->loop == 0) precmd(shell);
}

int exec_atty(shell_t* shell)
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

void exec_script(shell_t* shell, char* path)
{
    FILE* file = fopen(path, "r");
    char* line = NULL;
    size_t len = 0;
    ssize_t size = 0;
    if (file == NULL) {
        perror(path);
        exit(84);
    }
    while ((size = getline(&line, &len, file)) != -1) {
        if (size == 1) continue;
        if (size == EOF) break;
        if (clean_str(line)[0] == '#') {
            printf("comment\n");
            continue;
        }
        handle_command(parse_command(line, shell), shell);
    }
    fclose(file);
}

int main(int ac, char** av, char** envp)
{
    ssize_t size = 0; char* line = "";
    shell_t* shell = get_shell(init_shell(envp, av));
    if (exec_atty(shell))
        exit_detach_shm(shell);
    if (ac >= 2) {
        exec_script(shell, av[1]); exit_detach_shm(shell);
    }
    while (1) {
        my_putstr(get_prompt_prefix(), 1);
        size = my_getline(&line, shell);
        if (size == 1) continue;
        if (size == EOF) break;
        shell->loop = 0; shell->loop_postcmd = 0;
        handle_command(parse_command(line, shell), shell);
        line[size - 1] = '\0';
        set_var(shell, "_", line);
    }
    if (isatty(0)) write(1, "exit\n", 5);
    exit_detach_shm(shell);
    return (shell->state);
}
