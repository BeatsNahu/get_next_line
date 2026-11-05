/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alopez-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 11:59:10 by alopez-t          #+#    #+#             */
/*   Updated: 2026/11/05 14:49:51 by alopez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*read_and_accumulate(int fd, char *content, size_t *position)
{
	char	*tmp;
	ssize_t	bytes_read;

	tmp = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!tmp)
		return (cleaner(content));
	bytes_read = 1;
	while ((checker(content, position) == 0) && bytes_read > 0)
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read < 0)
			break ;
		tmp[bytes_read] = '\0';
		content = ft_strjoin(content, tmp);
	}
	free(tmp);
	if (bytes_read < 0 || !content || content[0] == '\0')
		return (cleaner(content));
	return (content);
}

char	*conffirm(char *content, size_t position)
{
	char	*line;
	size_t	len;

	if (content[position] == '\n')
		len = position + 1;
	else
		len = position;
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	ft_strcpy(line, content, len);
	line[len] = '\0';
	return (line);
}

char	*recover(char *content, size_t position)
{
	size_t	i;
	char	*tmp;

	if (content[position] != '\n' || !content[position + 1])
		return (cleaner(content));
	i = 0;
	while (content[position + 1 + i] != '\0')
		i++;
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (cleaner(content));
	ft_strcpy(tmp, &content[position + 1], i);
	tmp[i] = '\0';
	cleaner(content);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*content;
	char		*line;
	size_t		position;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	content = read_and_accumulate(fd, content, &position);
	if (!content)
		return (NULL);
	line = conffirm(content, position);
	if (!line)
	{
		content = cleaner(content);
		return (NULL);
	}
	content = recover(content, position);
	return (line);
}
