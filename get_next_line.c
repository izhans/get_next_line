/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 20:53:28 by isastre-          #+#    #+#             */
/*   Updated: 2024/12/19 16:29:00 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#ifndef BUFFER_SIZE
	#define BUFFER_SIZE 1
#endif

#include <stdio.h> // TODO: delete

void	populate_line(int fd, char **line);
int		has_new_line(char *line);
void	concat_buffer_to_line(char *buffer, char **line);
int		ft_strlen(char *str);
char	*ft_get_line(char **line);
int		where_is_new_line(char *line);
void	clean_line(char **line, int new_line_index);

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
	// printf("line after populate_line <%s>\n", line);
	if (line == NULL)
		return (NULL);
	char *next_line = ft_get_line(&line);
	// printf("line after ft_get_line -> line: <%s> - next_line: <%s>", line, next_line);
	return (next_line);
}

void	populate_line(int fd, char **line)
{
	char	*buffer;
	int		read_chars;

	while (!has_new_line(*line))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return ft_free(line);
		read_chars = read(fd, buffer, BUFFER_SIZE);
		if (read_chars <= 0) // error en read (-1) o EOF (0)
		{
			free(buffer);
			if (read_chars < 0 || ft_strlen(*line) == 0)
				ft_free(line);
			return ;
		}
		buffer[read_chars] = '\0'; // se coloca despues porque en caso de haber error estaria escribiendo en posiciones que no son mias
		concat_buffer_to_line(buffer, line);
		free(buffer); // ? free aqui o dentro de concat?
	}
}

int	has_new_line(char *line)
{
	while (*line)
	{
		if (*line == '\n')
			return (1);
		line++;
	}
	return (0);
}

void	concat_buffer_to_line(char *buffer, char **line)
{
	// printf("\t----concat_buffer_to_line starts----\n\n");
	int		line_len;
	int		buffer_len; // = read_chars // ? me compensa pasarlo como parametro de entrada
	char	*concatenated_line;
	int		i;
	int		j;

	// printf("\tline: %s buffer: %s\n", *line, buffer);
	line_len = ft_strlen(*line);
	buffer_len = ft_strlen(buffer);
	concatenated_line = malloc(line_len + buffer_len + 1);
	// printf("\tconcatenated_line size: %d\n", line_len + buffer_len + 1);
	i = 0;
	while ((*line)[i]) // ? puede dar error si *line es NULL
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
	// printf("\tACK: buffer copied\n");
	concatenated_line[i + j] = '\0';
	free(*line);
	*line = concatenated_line;
	// printf("\t----concat_buffer_to_line ends----\n\n");
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_get_line(char **line)
{
	// printf("----ft_get_line starts----\n\n");
	char	*next_line;
	int		new_line_index;
	int		i;

	if (ft_strlen(*line) == 0)
	{
		free(*line);
		return (NULL);
	}
	
	new_line_index = where_is_new_line(*line);
	next_line = malloc(new_line_index + 2); // ! +2: 1 por el \0 del final y el otro porque estoy obteniendo el index en vez del tamaño
	i = 0;
	while (i <= new_line_index)
	{
		next_line[i] = (*line)[i];
		i++;
	}
	next_line[i] = '\0';
	// printf("\tnext_line: <%s>\n", next_line);
	clean_line(line, new_line_index);
	// printf("----ft_get_line ends----\n\n");
	return (next_line);
}

int	where_is_new_line(char *line) // devuelve el index del \n -> a\n devuelve 1 [0: a][1: \n]
{
	int	i;

	i = 0;
	if (line == NULL) // ? esto no deberia poder pasar?
		return (0);
	while (line[i])
	{
		if (line[i] == '\n')
			return (i); // ? cambiar por un break para tener solo un return?
		i++;
	}
	return (i); // ! caso EOF
}

void	clean_line(char **line, int new_line_index)
{
	// printf("\t----clean_line starts----\n\n");
	int		line_len;
	char	*tmp_line;
	int		i;

	line_len = ft_strlen(*line);
	if (line_len == 0) // ? juraria que esto nunca puede ejecutarse porque se corta antes de llegar aqui
	{
		*line = NULL;
		return ;
	}
	if (line_len - new_line_index == 0)
		return ft_free(line);
	
	tmp_line = malloc(line_len - new_line_index); // no hay que hacer +1 porque estoy restando el index del \n y no la longitud hasta el
	i = 0;
	while ((*line)[new_line_index + 1])
	{
		tmp_line[i] = (*line)[new_line_index + 1];
		i++;
		new_line_index++;
	}
	tmp_line[i] = '\0';
	free(*line);
	*line = tmp_line;
	// printf("\tline: %s", *line);
	// printf("\t----clean_line ends----\n\n");
}
