#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	int   fd;
	char *line;
	int   i;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			perror("open");
			return (1);
		}
	}
	else
		fd = 0; 

	i = 1;
	while ((line = get_next_line(fd)))
	{
		printf("Line %d: %s", i, line);
		free(line);
		i++;
	}
	if (argc == 2)
		close(fd);
	return (0);
}

//  cc -Wall -Wextra -Werror  test.c get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=9 -o gnl_test
