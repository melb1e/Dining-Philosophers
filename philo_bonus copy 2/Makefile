# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mashad <mashad@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/22 11:06:15 by mashad            #+#    #+#              #
#    Updated: 2021/08/27 20:35:15 by mashad           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo_bonus
CC=gcc
FLAGS=-Wall -Werror -Wextra -pthread
SRCS=main.c errors.c defines.h philo.h

all: $(NAME)

$(NAME) : $(SRCS)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all
