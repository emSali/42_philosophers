# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esali <esali@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/18 13:16:13 by esali             #+#    #+#              #
#    Updated: 2023/09/01 16:30:50 by esali            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= philosophers

SRCS 		=	srcs/main.c srcs/init_args.c srcs/philosophers.c srcs/init_philos.c \
				srcs/getters.c

OBJS 		= $(SRCS:.c=.o)

CC			= gcc
RM			= rm
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address -g

all:		$(NAME)

$(NAME):	$(OBJS)
			gcc -g -pthread ${CFLAGS} ${OBJS} -o ${NAME}

clean:
			$(RM) $(OBJS)

fclean:
			$(RM) $(NAME) $(OBJS)

re: fclean all
