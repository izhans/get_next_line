#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line_bonus.h"

int main()
{
	int fd1;
	int fd2;
	int fd3;

	fd1 = open("test_files/file1", O_RDONLY);
	fd2 = open("test_files/file2", O_RDONLY);
	fd3 = open("test_files/file3", O_RDONLY);

	char *line;
	int i;

	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("fd %i\tline %d: %s", fd1, i, line);
		free(line);
		
		line = get_next_line(fd2);
		printf("fd %i\tline %d: %s", fd2, i, line);
		free(line);

		line = get_next_line(fd3);
		printf("fd %i\tline %d: %s", fd3, i, line);
		free(line);
		i++;
	}
	
	close(fd1);
	close(fd2);
	close(fd3);

	printf("---end---\n\n");

	return 0;
}
