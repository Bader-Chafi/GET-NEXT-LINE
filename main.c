#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.c"
int	main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char	*line;
	if (fd < 0)
	{
		line = get_next_line(fd);
		printf("%s", line);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}