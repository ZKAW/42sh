/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** input
*/

#include "mysh.h"

char *get_prompt_prefix(void)
{
    char *cwd = getcwd(NULL, 0);
    char **env = call_env(NULL);
    char *home = get_env_var(env, "HOME");
    char *prompt;

    if (strncmp(cwd, home, strlen(home)) == 0) {
        prompt = malloc(sizeof(char) * (strlen(cwd) + 5));
        strcpy(prompt, "~");
        strcat(prompt, cwd + strlen(home));
        strcat(prompt, " » ");
    } else {
        prompt = malloc(sizeof(char) * (strlen(cwd) + 5));
        strcpy(prompt, cwd);
        strcat(prompt, " » ");
    }

    free(cwd);

    return (prompt);
}
