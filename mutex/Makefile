# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmarcele <mmarcele@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/05 00:35:48 by mmarcele          #+#    #+#              #
#    Updated: 2022/07/11 12:35:00 by mmarcele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	dining_philosophers

SOURCES			:=	./sources
INCLUDES		:=	./includes
OBJECTS			:=	./objects

SRCS			:=	main.c \
					initialization.c \
					threads.c \
					life.c \
					status.c \
					death.c \
					errors.c \
					utils.c

HEADERS			:=	defines.h \
					philo.h

OBJS			:=	$(addprefix ${OBJECTS}/, $(SRCS:.c=.o))

CC				:=	clang
CFLAGS			:=	-Wall -Wextra -Werror
CINCLUDES		:=	-I ${INCLUDES}
CDEPENDENCIES	:=	-pthread -lpthread

NO_COLOR = \033[0m

TEXT = $(NO_COLOR)\033[0;34m
PRIMATY_TEXT = $(NO_COLOR)\033[1;36m

${OBJECTS}/%.o: ${SOURCES}/%.c ${INCLUDES}/defines.h ${INCLUDES}/philo.h Makefile
	@mkdir -p $(dir $@)
	@printf "$(TEXT)Successfully Created $(PRIMATY_TEXT)$@'s Object files $(TEXT)\n"
	@${CC} ${CFLAGS} -o $@ -c $< ${CINCLUDES}

all: ${NAME}

${NAME}: ${OBJS}
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${CDEPENDENCIES}
	@printf "$(TEXT)Successfully Created $(PRIMATY_TEXT)$@ $(TEXT)\n$(NO_COLOR)"


clean:
	@printf "$(TEXT)Cleaning $(PRIMATY_TEXT)$(NAME)'s Object files...\n"
	@rm -rf ${OBJECTS}

fclean: clean
	@printf "$(TEXT)Cleaning $(PRIMATY_TEXT)$(NAME)\n"
	@rm -f ${NAME}

norminette:
	@printf "$(TEXT)Checking norminette $(PRIMATY_TEXT)$(NAME)\n"
	norminette $(SOURCES) $(INCLUDES)

re: fclean all

.PHONY:	all clean fclean re norminette