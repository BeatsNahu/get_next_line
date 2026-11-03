/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alopez-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 12:00:27 by alopez-t          #+#    #+#             */
/*   Updated: 2026/10/22 17:46:25 by alopez-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

	#ifndef BUFFER_SIZE
		#define BUFFER_SIZE 1024
	#endif

#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd);

#endif
