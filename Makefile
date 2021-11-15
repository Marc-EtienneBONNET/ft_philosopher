# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbonnet <mbonnet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/04 15:14:49 by mbonnet           #+#    #+#              #
#    Updated: 2021/11/15 19:17:37 by mbonnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philosopher

SRCS			=	main.c\
					utile.c\
					initialisation/my_init_element.c\
					initialisation/my_parsage.c\
					routine/routine_gold.c\
					routine/routine_philos.c\

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
