/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 20:53:28 by isastre-          #+#    #+#             */
/*   Updated: 2024/12/11 14:19:07 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFER_SIZE 1

// TODO: change function names to ft_<function_name>
char	*get_next_line(int fd)
{
	static char	*line;

	populate_line(fd, &line);
	if (line == NULL)
		return (NULL);
	return (get_line(&line));
}

void	populate_line(int fd, char **line)
{
	char	*buffer;
	int		read_chars;

	while (!has_new_line(*line)) // ! plantear caso EOF
	{
		buffer = malloc(BUFFER_SIZE + 1); // TODO: null check
		read_chars = read(fd, buffer, BUFFER_SIZE);
		// TODO: ver si se pueden unificar estos 2 ifs
		if (read_chars < 0) // error en read (-1)
		{
			free(buffer);
			free(*line);
			*line = NULL;
			return ;
		}
		if (read_chars == 0) // EOF // ! esto esta mal planteado porque borro sin tener la ultima linea
		{
			free(buffer);
			*line = NULL; // ? esto ya deberia ser NULL?
			return ;
		}
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
	int		line_len;
	int		buffer_len; // = read_chars // ? me compensa pasarlo como parametro de entrada
	char	*concatenated_line;
	int		i;
	int		j;

	line_len = ft_strlen(*line);
	buffer_len = ft_strlen(buffer);
	concatenated_line = malloc(line_len + buffer_len + 1);
	i = 0;
	while (*line[i]) // ? puede dar error si *line es NULL
	{
		concatenated_line[i] = *line[i];
		i++;
	}
	j = 0;
	while (buffer[j])
	{
		concatenated_line[i + j] = buffer[j];
		j++;
	}
	concatenated_line[i + j] = '\0';
	free(line);
	line = &concatenated_line;
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

char	*get_line(char **line)
{
	char	*next_line;
	int		new_line_index;
	int		i;

	new_line_index = where_is_new_line(line);
	next_line = malloc(new_line_index + 2); // ! +2: 1 por el \0 del final y el otro porque estoy obteniendo el index en vez del tamaño
	i = 0;
	while (i <= new_line_index)
	{
		next_line[i] = *line[i];
		i++;
	}
	next_line[i] = '\0';
	clean_line(line, new_line_index);
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
	int		line_len;
	char	*tmp_line;
	int		i;

	line_len = ft_strlen(line);
	tmp_line = malloc(line_len - new_line_index); // no hay que hacer +1 porque estoy restando el index del \n y no la longitud hasta el
	i = 0;
	while (*line[new_line_index + 1])
	{
		tmp_line[i] = *line[new_line_index + 1];
		i++;
		new_line_index++;
	}
	tmp_line[i] = '\0';
	free(*line);
	line = tmp_line;
}
