# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jotavare <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/26 11:57:06 by jotavare          #+#    #+#              #
#    Updated: 2023/04/27 10:48:39 by jotavare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

HEADER		=	./include/

CC			=	gcc

CFLAGS		=	-Werror -Wall -Wextra -g -pthread -I $(HEADER)

SRCS		=	sources/main.c \
				sources/simulation.c \
				sources/threads.c \
				sources/init_and_parse.c \
				sources/check.c \
				sources/utilities.c \
				sources/time.c \

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean		:
				rm -rf $(OBJS)

fclean		:	clean
				rm -rf $(NAME)

re			:	fclean all
