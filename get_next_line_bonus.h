/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alopez-t <alopez-t@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 15:17:00 by alopez-t          #+#    #+#             */
/*   Updated: 2026/11/08 18:23:09 by alopez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_BONUS_H

# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
void				*recover(t_list **stash, t_list *tail);
char				*conffirm(t_list *stash);
void				*read_and_accumulate(int fd, t_list **stash, t_list **tail);

int					checker(t_list *node);
size_t				get_len_line(t_list *lst);
t_list				*ft_lstnew(void *content);
int					ft_lstadd_back(t_list **lst, t_list **tail, void *content);
void				*free_stash(t_list **list);

#endif
