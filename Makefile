# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esali <esali@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/18 13:16:13 by esali             #+#    #+#              #
#    Updated: 2023/10/16 11:36:27 by esali            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	philo

SRCS 		=	srcs/main.c srcs/init_philos.c srcs/init_args.c srcs/routine.c srcs/routine_util.c

OBJS 		=	$(SRCS:.c=.o)

CC			=	gcc
RM			=	rm
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=thread -g

all:		$(NAME)

$(NAME):	$(OBJS)
			gcc -g -pthread ${CFLAGS} ${OBJS} -o ${NAME}

clean:
			$(RM) $(OBJS)

fclean:
			$(RM) $(NAME) $(OBJS)

re: fclean all
