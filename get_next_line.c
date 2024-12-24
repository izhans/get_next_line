/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 20:53:28 by isastre-          #+#    #+#             */
/*   Updated: 2024/12/24 01:30:40 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#ifndef BUFFER_SIZE
	#define BUFFER_SIZE 1
#endif

#include <stdio.h> // TODO: delete

void	populate_line(int fd, char **line);
void	ft_concat_buffer_to_line(char *buffer, char **line, int buffer_len);
char	*ft_get_line(char **line);
void	ft_clean_line(char **line, int new_line_index);

// TODO: change function names to ft_<function_name>
char	*get_next_line(int fd)
{
	static char	*line;

	if (!line)
	{
		line = malloc(1);
		if (line == NULL)
			return (NULL);
		line[0] = '\0';
	}
	populate_line(fd, &line);
	if (line == NULL)
		return (NULL);
	return (ft_get_line(&line));
}

void	populate_line(int fd, char **line)
{
	char	*buffer;
	int		read_chars;

	while (!ft_has_new_line(*line))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return (ft_free(line));
		read_chars = read(fd, buffer, BUFFER_SIZE);
		if (read_chars <= 0) // error en read (-1) o EOF (0)
		{
			free(buffer);
			if (read_chars < 0 || ft_strlen(*line) == 0)
				ft_free(line);
			return ;
		}
		buffer[read_chars] = '\0'; // se coloca despues porque en caso de haber error estaria escribiendo en posiciones que no son mias
		ft_concat_buffer_to_line(buffer, line, read_chars);
		free(buffer);
	}
}

void	ft_concat_buffer_to_line(char *buffer, char **line, int buffer_len)
{
	int		line_len;
	char	*concatenated_line;
	int		i;
	int		j;

	line_len = ft_strlen(*line);
	concatenated_line = malloc(line_len + buffer_len + 1);
	if (concatenated_line == NULL)
		return (ft_free(line));
	i = 0;
	while ((*line)[i])
	{
		concatenated_line[i] = (*line)[i];
		i++;
	}
	j = 0;
	while (buffer[j])
	{
		concatenated_line[i + j] = buffer[j];
		j++;
	}
	concatenated_line[i + j] = '\0';
	free(*line);
	*line = concatenated_line;
}

char	*ft_get_line(char **line)
{
	char	*next_line;
	int		new_line_index;
	int		i;

	if (ft_strlen(*line) == 0)
		return (ft_free(line), NULL);
	new_line_index = ft_where_is_new_line(*line);
	next_line = malloc(new_line_index + 1);
	if (next_line == NULL)
		return (ft_free(line), NULL);
	i = 0;
	while (i < new_line_index)
	{
		next_line[i] = (*line)[i];
		i++;
	}
	next_line[i] = '\0';
	ft_clean_line(line, new_line_index);
	return (next_line);
}

void	ft_clean_line(char **line, int new_line_index)
{
	int		line_len;
	char	*tmp_line;
	int		i;

	line_len = ft_strlen(*line);
	if (line_len - new_line_index + 1 == 0)
		return ft_free(line);
	tmp_line = malloc(line_len - new_line_index + 1);
	if (tmp_line == NULL)
		return (ft_free(line));
	i = 0;
	while ((*line)[new_line_index])
	{
		tmp_line[i] = (*line)[new_line_index];
		i++;
		new_line_index++;
	}
	tmp_line[i] = '\0';
	free(*line);
	*line = tmp_line;
}
