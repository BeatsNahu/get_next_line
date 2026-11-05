/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alopez-t <alopez-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 12:00:27 by alopez-t          #+#    #+#             */
/*   Updated: 2026/11/05 14:54:38 by alopez-t         ###   ########.fr       */
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

char	*get_next_line(int fd);
char	*recover(char *content, size_t position);
char	*conffirm(char *content, size_t position);
char	*read_and_accumulate(int fd, char *content, size_t *position);

char	*cleaner(char *content);
int		checker(char *content, size_t *position);
size_t	ft_len(char *str);
void	*ft_strcpy(char *new, char *src, size_t n);
void	*ft_strjoin(char *content, char *buffer_tmp);

#endif
