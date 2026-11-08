/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alopez-t <alopez-t@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 15:16:40 by alopez-t          #+#    #+#             */
/*   Updated: 2026/11/08 18:14:21 by alopez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

int	checker(t_list *node)
{
	size_t	i;

	if (!node || !node->content)
		return (0);
	i = 0;
	while (node->content[i] && node->content[i] != '\n')
		i++;
	if (node->content[i] == '\n')
		return (1);
	return (0);
}

size_t	get_len_line(t_list *lst)
{
	size_t	len;
	size_t	i;

	len = 0;
	while (lst)
	{
		i = 0;
		while (lst->content[i])
		{
			if (lst->content[i] == '\n')
				return (len + 1);
			len++;
			i++;
		}
		lst = lst->next;
	}
	return (len);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
	{
		free(content);
		return (NULL);
	}
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

int	ft_lstadd_back(t_list **list, t_list **tail, void *content)
{
	t_list	*new;

	new = ft_lstnew(content);
	if (!new)
		return (0);
	if (!*list)
		*list = new;
	else
		(*tail)->next = new;
	*tail = new;
	return (1);
}

void	*free_stash(t_list **lst)
{
	t_list	*tmp_next;

	if (!lst || !*lst)
		return (NULL);
	while (*lst != NULL)
	{
		tmp_next = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp_next;
	}
	*lst = NULL;
	return (NULL);
}
