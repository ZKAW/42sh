/*
** EPITECH PROJECT, 2022
** mini-shell2
** File description:
** redirections.c
*/

#include "mysh.h"

void get_input(cmd_t* cmd)
{
    size_t len = 0;
    char** array = malloc(sizeof(char*));
    array[0] = NULL;
    char* line = "";

    while (1) {
        printf("? ");
        getline(&line, &len, stdin);
        array = array_append(array, line);
        if (strstr(line, cmd->input))
            break;
    }
    cmd->input = merge_array(array);
}

void guarantee_pipe(int fd[2], shell_t* shell)
{
    if (pipe(fd) == -1) {
        kill(shell->sub, SIGTERM);
        exit(1);
    }
}

// static int exec_pipe(shell_t *shell, int index)
// {
//     dup2(shell->parent_fd[0], 0);
//     if (index != shell->cmd->nb_pipes - 1)
//         dup2(shell->child_fd[1], 1);

//     close(shell->child_fd[0]);
//     close(shell->child_fd[1]);

//     shell->cmd = shell->pipes[index];
//     handle_redirs(shell);
//     exit(shell->return_code);
// }


// static void exec_command(shell_t *shell)
// {
//     int status;

//     close(shell->child_fd[1]);
//     shell->parent_fd[0] = shell->child_fd[0];
//     if (shell->cmd->index == shell->cmd->nb_pipes - 1) wait(&status);
//     int return_code = interpret_status(status, errno,
//                             shell->cmd->args[0], 0);
//     if (return_code != 0)
//         shell->return_code = return_code;
// }

// void handle_pipes(shell_t *shell)
// {
//     for (int i = 0; i < shell->cmd->nb_pipes; i++) {
//         shell->cmd->index = i;
//         if (create_pipe(shell->child_fd)) return;

//         pid_t pid = fork();
//         if (pid == -1) {
//             perror("fork");
//             shell->return_code = 1;
//             return;
//         }
//         if (pid == 0) exec_pipe(shell, i);

//         exec_command(shell);
//     }

//     close(shell->parent_fd[0]);
// }


int set_input(cmd_t* cmd, shell_t* shell, int fd[2])
{
    int file_fd;
    if (cmd->input_type == NONE)
        return 0;
    if (cmd->input_type == FILE_PATH) {
        file_fd = open(cmd->input, O_RDONLY);
        dup2(file_fd, 0);
        return 0;
    }
    guarantee_pipe(fd, shell);
    if (cmd->input_type == STD) {
        get_input(cmd);
        write(fd[1], cmd->input, strlen(cmd->input));
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
    }
    if (cmd->input_type == PIPE) {
        prepare_pipe(cmd, shell, fd);
    }
    return 0;
}

void set_output(cmd_t* cmd, int output_fd[2])
{
    int file_fd;
    if (cmd->output_type == FILE_PATH) {
        file_fd = open(cmd->output, O_RDWR | cmd->append | O_CREAT, 0644);
        dup2(file_fd, 1);
    }
    if (cmd->output_type == PIPE) {
        dup2(output_fd[1], 1);
        close(output_fd[1]);
    }
}
