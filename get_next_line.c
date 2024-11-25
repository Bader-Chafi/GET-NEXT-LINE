
// #include "get_next_line.h"
// #include <libc.h>   // all
// #include <fcntl.h>  // O_CREAT
// #include <unistd.h> // read
// #include <stdio.h>  // printf
// #include <stdlib.h> // malloc

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1

char *get_next_line(int fd)
{
    char buffer[BUFFER_SIZE + 1];
    long bytes_read;
    static char *str = NULL;
    char *temp;
    char *line;
    int i = 0;

    if (fd < 0) // || BUFFER_SIZE <= 0
        return (NULL);

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        if (!str)
            str = strdup(buffer);
        else
        {
            temp = str;
            str = malloc(strlen(temp) + bytes_read + 1);
            strcpy(str, temp);
            strcat(str, buffer);
            free(temp);
        }
        if (strchr(buffer, '\n'))
            break;
    }

    if (!str || str[0] == '\0')
        return (NULL);

    while (str[i] && str[i] != '\n')
        i++;

    line = malloc(i + 2);
    strncpy(line, str, i + (str[i] == '\n'));
    line[i + (str[i] == '\n')] = '\0';

    temp = str;
    str = strdup(str + i + (str[i] == '\n'));
    free(temp);

    return (line);
}

int main()
{
    int fd = open("test.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return 0;
}
