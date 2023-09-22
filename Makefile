# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esali <esali@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/18 13:16:13 by esali             #+#    #+#              #
#    Updated: 2023/09/22 17:27:13 by esali            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	philo

SRCS 		=	srcs/main.c srcs/init_philos.c srcs/init_args.c srcs/philos.c

#SRCS 		=	srcs/old/main_old.c srcs/old/init_args.c srcs/old/philosophers.c srcs/old/init_philos.c

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
