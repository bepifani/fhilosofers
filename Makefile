# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bepifani <bepifani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/12 15:29:23 by bepifani          #+#    #+#              #
#    Updated: 2022/03/12 17:41:57 by bepifani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra -c

SRC_FILES = philo.c	utils.c

OBJECTS = $(SRC_FILES:.c=.o)

HEADER = philo.h


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

.PHONY: all clean fclean re bonus