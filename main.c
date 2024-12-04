#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main()
{
	int filename;
	int fd;

	filename = "txt";
	fd = open(filename, O_RDONLY);

	char *line;

	while (line = get_next_line(fd))
	{
		printf("%s", line);
		free(line);
	}
	
	close(fd);

	return 0;
}
