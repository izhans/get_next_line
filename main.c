#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int main()
{
	char *filename;
	int fd;

	filename = "txt";
	fd = open(filename, O_RDONLY);

	char *line;
	int i;

	i = 0;
	// while (i < 10)
	while ((line = get_next_line(fd)))
	{
		// line = get_next_line(fd);
		printf("line %d: %s", i, line);
		free(line);
		i++;
	}
	
	close(fd);

	return 0;
}
