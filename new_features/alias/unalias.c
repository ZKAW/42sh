/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** unalias
*/

alias_t *delete_last_element(alias_t *alias)
{
    alias_t *tmp;
    alias_t *tmp2;
    for (tmp = alias; tmp->next != NULL; tmp = tmp->next) {
        tmp2 = tmp;
    }
    tmp2->next = NULL;
    free(tmp);
    return (alias);
}

alias_t *unalias(char* argv, shell_t *shell)
{
    char **buffer = tokenize_string(argv, " \n");
    alias_t *tmp;
    alias_t *tmp2;
    if (buffer[1] == NULL) {
        my_putstr("unalias: Too few arguments.\n");
        return (shell->alias);
    }
    if (my_strcmp(buffer[1], "*") == 0) {
        for (tmp = shell->alias; tmp != NULL; tmp = tmp2) {
            tmp2 = tmp->next;
            free(tmp);
        }
        shell->alias = malloc(sizeof(alias_t));
        shell->alias->alias = NULL;
        shell->alias->command = NULL;
        shell->alias->next = NULL;
        return (shell->alias);
    }
    for (tmp = shell->alias; tmp->next != NULL; tmp = tmp->next) {
        if (my_strcmp(tmp->alias, buffer[1]) == 0) {
            tmp2 = tmp->next;
            tmp->alias = tmp2->alias;
            tmp->command = tmp2->command;
            tmp->next = tmp2->next;
            free(tmp2);
            return (shell->alias);
        }
    }
    if (my_strcmp(tmp->alias, buffer[1]) == 0) {
        return(delete_last_element(shell->alias));
    }
    my_putstr("Alias not found\n");
    return (shell->alias);
}
