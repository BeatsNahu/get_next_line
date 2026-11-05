# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alopez-t <alopez-t@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/11/04 10:14:03 by alopez-t          #+#    #+#              #
#    Updated: 2026/11/05 14:59:18 by alopez-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rcs
NAME		= GNL.a

SRCS_M		= get_next_line.c get_next_line_utils.c
SRCS_B		= get_next_line_bonus.c get_next_line_utils_bonus.c

OBJS_M		= $(SRCS_M:.c=.o)
OBJS_B		= $(SRCS_B:.c=.o)

HEADER_M	= get_next_line.h
HEADER_B	= get_next_line_bonus.h

all: $(NAME)

$(NAME): $(OBJS_M) Makefile FORCE
	rm -f $(NAME)
	$(AR) $(NAME) $(OBJS_M)

bonus: $(OBJS_B) FORCE
	rm -f $(NAME)
	$(AR) $(NAME) $(OBJS_B)

$(OBJS_M): %.o: %.c $(HEADER_M) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_B): %.o: %.c $(HEADER_B) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_M) $(OBJS_B)

fclean: clean
	rm -f $(NAME)

re: fclean all

re_bonus: fclean bonus

norminette:
	@norminette $(SRCS_M) $(SRCS_B) $(HEADER_M) $(HEADER_B)

FORCE:

.PHONY: all bonus clean fclean re re_bonus norminette FORCE
