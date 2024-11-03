/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:34:42 by isastre-          #+#    #+#             */
/*   Updated: 2024/11/03 20:45:18 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define BUFFER_SIZE 10

int	ft_read_line(int fd, char *line);

char	*get_next_line(int fd)
{
	static char	*line;
	

	if (!line)
		line = "";
	
	if (ft_read_line(fd, line) == 0) // TODO free line + return NULL // add read error to same check?
		return (NULL);
	
	return (line);
}


int	ft_read_line(int fd, char **line)
{
	char		*buffer;
	ssize_t		len;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	len = read(fd, buffer, BUFFER_SIZE); // TODO check read error (returns -1)
	if (len == 0) // has reached EOF
	{
		free(buffer); // TODO where do I free line
		return (0);
	}
	
	buffer[BUFFER_SIZE] = '\0';

	*line = ft_strjoin(*line, buffer);
	if (ft_strchr(buffer, '\0') < BUFFER_SIZE)
	{
		printf("buffer: %s\n", buffer);
		printf("line: %s\n", *line);
		ft_read_line(fd, *line);
	}
	printf("lline: %s\n", *line);
	return (len);
}

int	ft_strchr(const char *s, char ch)
{
	int	i;

	i = 0;
	if (ch == '\0')
		return ft_strlen(s);
	while (s[i])
	{
		if (s[i] == ch)
			return (i);
		i++;
	}
	return (-1);
}