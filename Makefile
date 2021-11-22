# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/04 15:14:49 by mbonnet           #+#    #+#              #
#    Updated: 2021/11/22 18:40:03 by mbonnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philosopher

SRCS			=	main.c\
					parse/my_parse.c\
					init_philo_info/my_init_philo_info.c\
					routine/my_routine.c\
					routine/utile.c\
					routine/my_action.c\
					

OBJS			=	${addprefix srcs/,${SRCS:.c=.o}}

HEAD			=	-I includes -I libft/includes

CC				=	gcc

CFLAGS			=	-Wall -Werror -Wextra -g -pthread -fsanitize=thread

LIBFT_DIR		=	libft

LDFLAGS			=	-L ${LIBFT_DIR} -lft

.c.o			:
					${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.c=.o}

$(NAME)			:	${OBJS}
					make -C ${LIBFT_DIR}
					${CC} ${CFLAGS} ${OBJS} ${LDFLAGS} -o ${NAME}


all				:	${NAME}

clean			:
					make clean -C ${LIBFT_DIR}
					rm -rf ${OBJS}

fclean			:	clean
					make fclean -C ${LIBFT_DIR}
					rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re
