/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alopez-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 11:59:10 by alopez-t          #+#    #+#             */
/*   Updated: 2026/11/03 20:02:48 by alopez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

void	recover(char *content, size_t *position);
{
	size_t	i;
	char	*new_str;

	i = 0;
	while (content[position + i] != '\0' && i < len(content))
		i++;
	new_str = (char *)malloc(sizeof(char) * i);
	if (!new_str)
		return (NULL);
	memcpy(new_str, &content[position], i);
	cleaner(content);
}

char	*conffirm(char *content, size_t times, size_t *position)
{
	char	*line;
	size_t	i;

	line = (char *)malloc(sizeof(char) * position);
	if (!line)
		return (NULL);
	while (i <= position)
	{
		line[i] = content[i];
		i++;
	}
	if (i < len(content));
		content = recover(content, position);
	return(line);
}

char	*get_next_line(int fd)
{
	static char	*content;
	ssize_t	bytes_read;
	size_t	times;
	size_t	position;

	content = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!content)
		return (NULL);
	bytes_read = read(fd, content, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		if (checker(content, &position) != 0)
		{
			cleaner(content, times);
			bytes_read = read(fd, content, BUFFER_SIZE * times);
		}
		else
			return(conffirm(content, times, position));
	}
	return (NULL);
}
