// #include <libc.h>
// #include "get_next_line.h"


// int main()
// {
//     int i = open("test.txt", O_CREAT | O_RDWR, 0777);
//     read(i ,"test.txt", 1000);
//     return 1;
// }

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 1

void read_file(const char *filename)
{
    int fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // Open the file
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        write(2, "Error opening file\n", 19);
        return;
    }

    // Read the file byte by byte
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        write(1, buffer, bytes_read); // Write to standard output
    }

    // Check for read error
    if (bytes_read < 0)
    {
        write(2, "Error reading file\n", 19);
    }

    // Close the file
    close(fd);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        write(2, "Usage: ./program <filename>\n", 28);
        return 1;
    }

    read_file(argv[1]);
    return 0;
}
