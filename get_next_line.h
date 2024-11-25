#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H


#include <libc.h> // all
#include <fcntl.h> // O_CREAT
#include <unistd.h>  // read
#include <stdio.h> // printf
#include <stdlib.h> // malloc


char *get_next_line(int fd);




#endif