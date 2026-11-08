/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alopez-t <alopez-t@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 15:16:56 by alopez-t          #+#    #+#             */
/*   Updated: 2026/11/08 18:26:13 by alopez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

void	*read_and_accumulate(int fd, t_list **stash, t_list **tail)
{
	char	*tmp;
	ssize_t	bytes_read;

	bytes_read = 1;
	while (!checker((*tail)) && bytes_read > 0)
	{
		tmp = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
		if (!tmp)
			return (free_stash(stash));
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read <= 0)
			free(tmp);
		else
		{
			tmp[bytes_read] = '\0';
			if (!ft_lstadd_back(stash, tail, tmp))
				return (free_stash(stash));
		}
	}
	if (bytes_read < 0)
		return (free_stash(stash));
	return (NULL);
}

char	*conffirm(t_list *stash)
{
	char	*line;
	size_t	i;
	size_t	k;

	line = (char *)malloc(sizeof(char) * (get_len_line(stash)) + 1);
	if (!line)
		return (NULL);
	k = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			line[k++] = stash->content[i];
			if (stash->content[i] == '\n')
			{
				line[k] = '\0';
				return (line);
			}
			i++;
		}
		stash = stash->next;
	}
	line[k] = '\0';
	return (line);
}

void	*recover(t_list **stash, t_list *tail)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	i = get_len_line(tail);
	if (!tail->content[i])
		return (free_stash(stash));
	j = 0;
	while (tail->content[i + j])
		j++;
	new_str = (char *)malloc(sizeof(char) * j + 1);
	if (!new_str)
		return (free_stash(stash));
	j = 0;
	while (tail->content[i])
		new_str[j++] = tail->content[i++];
	new_str[j] = '\0';
	free_stash(stash);
	tail = ft_lstnew(new_str);
	return (*stash = tail);
}

char	*get_next_line(int fd)
{
	static t_list	*stash[OPEN_MAX];
	t_list			*tail[OPEN_MAX];
	char			*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	tail[fd] = stash[fd];
	read_and_accumulate(fd, &stash[fd], &tail[fd]);
	if (!stash[fd] || !tail[fd])
		return (NULL);
	line = conffirm(stash[fd]);
	if (!line)
		return (free_stash(&stash[fd]));
	recover(&stash[fd], tail[fd]);
	return (line);
}
