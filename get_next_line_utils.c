/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alopez-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 13:23:45 by alopez-t          #+#    #+#             */
/*   Updated: 2026/11/03 20:02:50 by alopez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

void	cleaner(char *content)
{
	free(content);	
}

int	checker(char *content, size_t *position)
{
	size_t	i;

	i = 0;
	while (content[i] != '\n' && content[i] != '\0')
		i++;
	position = i;
	if (content[i] == '\n' || content[i] == '\0')
		return (1);
	return (0);
}

size_t	len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*memcpy(char *new, char *src, size_t i)
{
	size_t i;

	i = 0;
	while (i != n)
	{
		new[i] = src[i];
		i++;
	}
}
