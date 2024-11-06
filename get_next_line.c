/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:34:42 by isastre-          #+#    #+#             */
/*   Updated: 2024/11/06 22:20:15 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define BUFFER_SIZE 3

int	ft_check_new_line(char *s)
{
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

int	ft_get_new_line_index(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_read(int fd, char **buffer)
{
	ssize_t		len;
	
	*buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	len = read(fd, *buffer, BUFFER_SIZE);
	if (len == -1)
	{
		free(*buffer);
		buffer = NULL;
		return (-1);
	}
	*buffer[BUFFER_SIZE] = '\0';

	return (len);
}

char	*ft_get_line(char **line)
{
	// printf("line get_line: %s\n", *line);
	int	n;
	char	*new_line;
	char	*temp_line;

	n = ft_get_new_line_index(*line) + 1;
	// printf("n: %i\n", n);
	if (n == -1)
		return (*line);
	
	new_line = ft_substr(*line, 0, n);

	temp_line = ft_strdup(*line + n);
	free(*line);
	*line = temp_line;
	// printf("temp_line: %s\n", temp_line);

	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*buffer;
	int			read_code;

	if (!line)
		line = malloc(0);
	buffer = NULL;
	

	read_code = ft_read(fd, &buffer);
	line = ft_strjoin(line, buffer);
		// printf("line: %s\n", line);
	
	while (!ft_check_new_line(line) && read_code == BUFFER_SIZE)
	{
		read_code = ft_read(fd, &buffer);
		line = ft_strjoin(line, buffer);
		// printf("line in: %s\n", line);
	}
	
	if (read_code <= 0)// TODO free
		return (NULL);
	
	return (ft_get_line(&line));
}
