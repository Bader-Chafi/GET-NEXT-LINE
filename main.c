#include "get_next_line.h"
# include <stdio.h>

int main()
{
    int fd = open("test.txt", O_CREAT | O_RDWR, 0777); // Use proper permissions for creation
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return 0;
}