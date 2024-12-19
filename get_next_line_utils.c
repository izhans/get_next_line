/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:23:17 by isastre-          #+#    #+#             */
/*   Updated: 2024/12/19 16:39:59 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char **line)
{
	free(*line);
	*line = NULL;
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
