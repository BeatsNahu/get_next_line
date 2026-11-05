/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alopez-t <alopez-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 14:52:50 by alopez-t          #+#    #+#             */
/*   Updated: 2026/11/05 14:52:55 by alopez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*content[OPEN_MAX];
	char		*line;
	size_t		position;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	content[fd] = read_and_accumulate(fd, content[fd], &position);
	if (!content[fd])
		return (NULL);
	line = conffirm(content[fd], position);
	if (!line)
	{
		content[fd] = cleaner(content[fd]);
		return (NULL);
	}
	content[fd] = recover(content[fd], position);
	return (line);
}
