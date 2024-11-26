#include "get_next_line.h"

int main()
{
    int fd = open("test.txt", O_CREAT);
    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    // if ((line = get_next_line(-1)) == NULL)
    //     printf("%s", line);
    return 0;
}