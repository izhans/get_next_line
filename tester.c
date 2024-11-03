#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

char *ft_read(int fd, int BUFFER_SIZE);

int main()
{
	char	*str = NULL;
	char	*filename = "txt";
	int		fd = open(filename, O_RDONLY);

	if (fd == -1)
		return (-1);
	
	do
	{
		str = get_next_line(fd);
		printf(">%s", str);
	} while (str != NULL);
	
	close(fd);

	return (0);
}
