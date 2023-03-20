/*
** EPITECH PROJECT, 2022
** BSQ
** File description:
** load_file_in_mem.c
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

char* load_file_in_mem(char const * filepath)
{
    int fd = 0;
    struct stat filestat;
    char* buffer;
    stat(filepath, &filestat);
    if (filestat.st_size == 0)
        return NULL;
    buffer = malloc(sizeof(char) * (filestat.st_size + 1));
    fd = open(filepath, O_RDONLY);
    if (fd < 0)
        return NULL;
    int r = read(fd, buffer, filestat.st_size);
    buffer[r] = '\0';
    return buffer;
}
