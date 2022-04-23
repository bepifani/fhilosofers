# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bepifani <bepifani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/21 20:52:48 by bepifani          #+#    #+#              #
#    Updated: 2022/04/23 21:08:20 by bepifani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = gcc
CFLAGS = -Wall -Werror -Wextra -c

SRC_FILES = philo_bonus.c	utils_bonus.c	init_bonus.c	utils2_bonus.c	action_bonus.c

OBJECTS = $(SRC_FILES:.c=.o)

HEADER = philo_bonus.h


OBJ = $(OBJECTS)


all: $(NAME)

$(NAME): $(OBJ) $(HEADER) 
	$(CC) $(OBJ) -o $@
	
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $< -o $@ 

	
clean:
	/bin/rm -f $(OBJECTS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re