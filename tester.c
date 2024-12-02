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
void	ft_realloc(char *leftover, char *buffer) // ! UNUSED
{
	ssize_t	buffer_len;
	size_t	leftover_len;
	size_t	realloc_size;
	char	*leftover2;

	leftover_len = strlen(leftover);
	buffer_len = strlen(buffer);

	realloc_size = leftover_len + (size_t) buffer_len + 1;
	leftover2 = realloc(leftover, realloc_size);
	strcat(leftover2, buffer);
	leftover2[realloc_size] = '\0';
	// free(leftover);
	leftover = leftover2;

	// printf("free at realloc %p\n", buffer);
	// free(buffer);
}

char	*ft_get_line(char **leftover, char *new_line);
int ft_read_and_alloc(int fd, char **leftover, int BUFFER_SIZE);

char *ft_read(int fd, int BUFFER_SIZE)
{
	static char	*leftover;
	char		*new_line;
	char		*line;

	// initialize leftover on the 1st execution of the function
	if (leftover == NULL)
		leftover = malloc(0);
	
	// read and add the readed content to leftover
	int r = ft_read_and_alloc(fd, &leftover, BUFFER_SIZE);

	// if read gives error or there is not any line to return
	if (r == -1)
		return (NULL);
	
	// if leftover does not contain a line to return, keep reading
	while (!strchr(leftover, '\n') && r == 1)
	{
		r = ft_read_and_alloc(fd, &leftover, BUFFER_SIZE);
	}
	
	// save \n position
	new_line = strchr(leftover, '\n');

	// get and return the line
	line = NULL;
	if (new_line)
		line = ft_get_line(&leftover, new_line);
	else if (r == 0 && strlen(leftover) > 0) // last line (EOF) case
		line = ft_get_line(&leftover, strchr(leftover, '\0'));
	
	return (line);
}

/**
 * @return 	-1 si hay error o es EOF y no queda nada en leftover
 * 			0 si no ha leido nada -> EOF
 * 			1 si ha leido (y realocado)
 */
int ft_read_and_alloc(int fd, char **leftover, int BUFFER_SIZE)
{
	char		*buffer;
	ssize_t		buffer_len;

	// printf("\nleftover [%s]\n\n", leftover);
	buffer = malloc(BUFFER_SIZE + 1);
	buffer_len = read(fd, buffer, BUFFER_SIZE);
	buffer[BUFFER_SIZE] = '\0';
	// printf("buf_len: %zu\t- leftover_len: %zu ", buffer_len, strlen(leftover));

	// read error or nothing read and nothing left on leftover
	if (buffer_len == -1 || (buffer_len == 0 && strlen(*leftover) == 0))
	{
		return (-1);
	}
	
	// something read
	if (buffer_len != 0)
	{
		// ft_realloc(*leftover, buffer);
		char	*old_leftover = *leftover;
		*leftover = ft_strjoin(*leftover, buffer);

		// printf("free buffer %p\n", buffer);
		free(buffer);

		// printf("free old_leftover %p\n", buffer);
		free(old_leftover);
		return (1);
	}
	// printf("\n\nleftover before realloc [%s]\n\n", leftover);

	// nothing read but there are still things on leftover
	return (0);
}

char	*ft_get_line(char **leftover, char *new_line)
{
	char		*line;

	// step 2 - get line
	ssize_t	line_len;
	
	line_len = new_line - *leftover + 1;
	line = malloc(line_len + 1);
	// printf("%zu - ", line_len);
	strncpy(line, *leftover, line_len); // +1 por el \0 final
	line[line_len] = '\0';

	// step 3 - quit line from leftover
	size_t	new_leftover_len;
	char	*new_leftover;

	new_leftover_len = strlen(new_line + 1);
	new_leftover = malloc(new_leftover_len + 1);
	strcpy(new_leftover, new_line + 1);
	new_leftover[new_leftover_len] = '\0';

	// printf("free %p\n", leftover);
	free(*leftover);
	*leftover = new_leftover;

	return (line);
}



int main(int argc, char **argv)
{
	char	*str = NULL;
	char	*filename = "txt2";
	int		fd = open(filename, O_RDONLY);
	int		BUFFER_SIZE = (argc == 2) ? atoi(argv[1]) : 12;

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
		str = ft_read(fd, BUFFER_SIZE);
		printf(">%s", str);
	} while (str != NULL);
	free(str);
	
	close(fd);

	return (0);
}
