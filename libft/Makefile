# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 14:31:03 by saseo             #+#    #+#              #
#    Updated: 2023/04/18 16:25:13 by yecnam           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
CC		= cc
CFLAGS 	= -Wall -Wextra -Werror
HEADER	= libft.h
SRCS	= ft_memcmp.c ft_strlen.c ft_calloc.c ft_bzero.c ft_isdigit.c \
	  ft_isalpha.c ft_strlcpy.c ft_substr.c ft_strjoin.c ft_strncpy.c \
	  ft_strdup.c ft_strcpy.c ft_strcmp.c ft_split.c ft_strchr.c \
	  ft_itoa.c ft_strstr.c ft_strncpy.c ft_atoi.c \
	  ft_stack_init.c ft_push.c ft_pop.c ft_new_stack_node.c ft_free_stack.c

OBJS	= $(SRCS:c=o) 

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)
	
$(NAME): $(OBJS)
	ar -rcs $@ $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
