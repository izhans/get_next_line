/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:23:17 by isastre-          #+#    #+#             */
/*   Updated: 2024/12/24 01:10:05 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char **line)
{
	free(*line);
	*line = NULL;
}

int	ft_has_new_line(char *line)
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

/**
 * @param line the line in which to find the \n
 * @returns the index of the \n + 1 OR the length of the string if there is no \n
 * @example a\n	[0:a][1:\n] -> returns 2 (index of \n + 1)
 * @example a	[0:a][1:\0] -> returns 2 (strlen)
 * 								(because it adds 1 before null checking line[i])
 */
int	ft_where_is_new_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}
