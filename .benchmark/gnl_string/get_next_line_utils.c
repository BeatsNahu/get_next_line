/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alopez-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 13:23:45 by alopez-t          #+#    #+#             */
/*   Updated: 2026/11/05 14:35:20 by alopez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*cleaner(char *content)
{
	free(content);
	return (NULL);
}

int	checker(char *content, size_t *position)
{
	size_t	i;

	if (!content)
		return (0);
	i = 0;
	while (content[i] != '\n' && content[i] != '\0')
		i++;
	*position = i;
	if (content[i] == '\n')
		return (1);
	return (0);
}

size_t	ft_len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_strcpy(char *new, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i != n)
	{
		new[i] = src[i];
		i++;
	}
	return (new);
}

void	*ft_strjoin(char *content, char *buffer_tmp)
{
	char	*new_str;
	size_t	sz_content;
	size_t	sz_tmp;

	if (!content)
	{
		content = (char *)malloc(1);
		if (!content)
			return (NULL);
		content[0] = '\0';
	}
	sz_content = ft_len(content);
	sz_tmp = ft_len(buffer_tmp);
	new_str = (char *)malloc(sizeof(char) * (sz_content + sz_tmp + 1));
	if (!new_str)
		return (cleaner(content));
	ft_strcpy(new_str, content, sz_content);
	ft_strcpy(&new_str[sz_content], buffer_tmp, sz_tmp);
	new_str[sz_content + sz_tmp] = '\0';
	cleaner(content);
	return (new_str);
}
