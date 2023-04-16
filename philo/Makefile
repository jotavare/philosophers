# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jotavare <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/10 16:40:18 by jotavare          #+#    #+#              #
#    Updated: 2023/04/15 21:28:26 by jotavare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# BASIC
CC = cc -g
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf
GDB = gdb

# TESTING
VAL = valgrind --leak-check=full --track-origin=yes
SANATIZE = -fsanitize=thread -g
HELGRIND = valgrind --tool=helgrind
DRD = valgrind --tool=drd

# COLORS
RESET			:= \033[0m
GREEN			=	\e[32m
CYAN			:= \33[1;36m
YELLOW			=	\e[033m
BLUE			=	\e[34m
WHITE			=	\e[00m
RED				:= \033[1;31m
BOLD			:= \033[1;1m

# PHILOSOPHERS
NAME = philo.a
SRCS =  check.c \
        utils.c \
        philo.c

OBJSDIR = objects
OBJS = $(addprefix $(OBJSDIR)/,$(SRCS:.c=.o))

# MAKE RULES
all: $(NAME) philo

$(NAME): $(OBJS)
	@echo "$(GREEN)$(BOLD)Creating objects directory...$(RESET)"
	ar -rcs $(NAME) $(OBJS)
	@echo "$(GREEN)$(BOLD)Objects created!$(RESET)"
	
$(OBJSDIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

philo: $(PHILO_OBJ) $(NAME)
	@echo "$(GREEN)$(BOLD)Creating executable...$(RESET)"
	$(CC) $(CFLAGS) $(PHILO_OBJ) $(NAME) -o philo
	@echo "$(GREEN)$(BOLD)Executable created!$(RESET)"

clean:
	@echo "$(YELLOW)$(BOLD)Removing objects...$(RESET)"
	$(RM) $(OBJSDIR)
	@echo "$(YELLOW)$(BOLD)Objects removed!$(RESET)"

fclean: clean
	@echo "$(RED)$(BOLD)Removing executable...$(RESET)"
	$(RM) philo philo.a
	@echo "$(RED)$(BOLD)Executable removed!$(RESET)"

re: fclean all
	@echo "$(GREEN)$(BOLD)Recompiled successfully!$(RESET)"

.SILENT:
