#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

#include <string.h>

/**
 * This function reallocs leftover to concatenate buffer
 * @param leftover the content from the last read that wasnt in the returned line
 * @param buffer the content that has been read in the current call to gnl
 */
void	ft_realloc(char *leftover, char *buffer)
{
	ssize_t	buffer_len;
	size_t	strl;
	size_t	realloc_size;
	char	*leftover2;

	strl = strlen(leftover);
	buffer_len = strlen(buffer);

	realloc_size = strl + (size_t) buffer_len;
	leftover2 = realloc(leftover, realloc_size);
	strcat(leftover2, buffer);
	// free(leftover);
	leftover = leftover2;

	free(buffer);
}

char	*ft_get_line(char **leftover, char *new_line);

char *ft_read(int fd, int BUFFER_SIZE)
{
	static char	*leftover;
	char		*buffer;
	ssize_t		buffer_len;
	char		*new_line;
	// char		*line;

	if (leftover == NULL)
		leftover = malloc(0);
	// line = NULL;
	// previous phase: read and add to leftover
	buffer = malloc(BUFFER_SIZE + 1);
	buffer_len = read(fd, buffer, BUFFER_SIZE);
	buffer[BUFFER_SIZE] = '\0';
	// TODO check read error (-1)

	ft_realloc(leftover, buffer);
	
	// step 1 - find \n
	new_line = strchr(leftover, '\n');

	if (new_line)
	{
		// step 4 - return line
		return (ft_get_line(&leftover, new_line));
	}
	
	// step 4 - return line -> if there is not a new line is NULL (for the moment)
	return (NULL);
	}

char	*ft_get_line(char **leftover, char *new_line)
{
	char		*line;

	// step 2 - get line
	ssize_t	line_len;
	
	line_len = new_line - *leftover + 1;
	line = malloc(line_len + 1);
	printf("%zu - ", line_len);
	strncpy(line, *leftover, line_len); // +1 por el \0 final
	line[line_len] = '\0';

	// step 3 - quit line from leftover
	size_t	new_leftover_len;
	char	*new_leftover;

	new_leftover_len = strlen(new_line + 1);
	new_leftover = malloc(new_leftover_len + 1);
	strcpy(new_leftover, new_line + 1);
	new_leftover[new_leftover_len] = '\0';

	free(*leftover);
	*leftover = new_leftover;

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
	free(str);
	
	close(fd);

	return (0);
}
