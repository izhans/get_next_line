/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 20:53:54 by isastre-          #+#    #+#             */
/*   Updated: 2024/12/24 01:03:05 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h> // creo que esta es solo necesaria para el main (close)
#include <stdlib.h>

char	*get_next_line(int fd);
// utils
void	ft_free(char **line);
int		ft_has_new_line(char *line);
int		ft_strlen(char *str);
int		ft_where_is_new_line(char *line);
