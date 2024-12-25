/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:23:17 by isastre-          #+#    #+#             */
/*   Updated: 2024/12/25 20:06:50 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief frees the line and sets its pointer to NULL
 * @param line a pointer to the line
 */
void	ft_free(char **line)
{
	free(*line);
	*line = NULL;
}

/**
 * @brief search for a \n
 * @param line the line in which to search
 * @returns 1 if a \n is found, 0 if not
 */
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

/**
 * @brief measures the length of a string
 * @param str the string to measure
 * @returns the length of the string or 0 if its NULL
 */
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
 * @brief returns the index after the first \n or the \0 index if there is no \n
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
