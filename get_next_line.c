/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:34:42 by isastre-          #+#    #+#             */
/*   Updated: 2024/11/03 19:12:22 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define BUFFER_SIZE 12

char	*get_next_line(int fd)
{
	char	*buffer;
	ssize_t	len;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	len = read(fd, buffer, BUFFER_SIZE);
	if (len == 0)
	{
		free(buffer);
		return (NULL);
	}
	
	buffer[BUFFER_SIZE] = '\0';
	
	return (buffer);
}
