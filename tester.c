#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

#include <string.h>

char *ft_read(int fd, int BUFFER_SIZE)
{
	static char	*leftover;
	char		*buffer;
	ssize_t		buffer_len;
	char		*leftover2;
	char		*new_line;
	char		*line;

	if (leftover == NULL)
		leftover = malloc(0);
	line = NULL;
	// previous phase: read and add to leftover
	buffer = malloc(BUFFER_SIZE + 1);
	buffer_len = read(fd, buffer, BUFFER_SIZE);
	buffer[BUFFER_SIZE] = '\0';
	// TODO check read error (-1)

	// TODO realloc leftover
	size_t strl = strlen(leftover);
	size_t realloc_size = strl + (size_t) buffer_len;
	leftover2 = realloc(leftover, realloc_size);
	strcat(leftover2, buffer);
	// free(leftover);
	leftover = leftover2;
	
	// step 1 - find \n
	new_line = strchr(leftover, '\n');

	if (new_line)
	{
		// step 2 - get line
		ssize_t	line_len;
		
		line_len = new_line - leftover + 1;
		line = malloc(line_len + 1);
		printf("%zu - ", line_len);
		strncpy(line, leftover, line_len); // +1 por el \0 final
		line[line_len] = '\0';

		// step 3 - quit line from leftover
		size_t	new_leftover_len;
		char	*new_leftover;

		new_leftover_len = strlen(new_line + 1);
		new_leftover = malloc(new_leftover_len + 1);
		strcpy(new_leftover, new_line + 1);
		new_leftover[new_leftover_len] = '\0';

		free(leftover);
		leftover = new_leftover;
	}
	
	free(buffer);
	// step 4 - return line
	return (line);
}



int main(int argc, char **argv)
{
	char	*str = NULL;
	char	*filename = "txt";
	int		fd = open(filename, O_RDONLY);

	if (fd == -1)
		return (-1);
	
	(void) argc;
	// str = ft_read(fd, atoi(argv[1]));
	// printf("str: <%s>", str);
	// str = ft_read(fd, atoi(argv[1]));
	// printf("str: <%s>", str);

	do
	{
		// str = get_next_line(fd);
		str = ft_read(fd, atoi(argv[1]));
		printf(">%s", str);
	} while (str != NULL);
	
	close(fd);

	return (0);
}
