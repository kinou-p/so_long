# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apommier <apommier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/13 16:27:49 by apommier          #+#    #+#              #
#    Updated: 2022/02/14 23:44:46 by apommier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= so_long
SRCS	= srcs/main.c\
			srcs/parsing.c\
			srcs/utils.c\
			srcs/print_map.c
OBJS	= ${SRCS:.c=.o}
CC		= gcc 
LIB		= -L ./mlx -lmlx -lXext -lX11
CFLAGS	= -g -Wall -Wextra
RM		= rm -rf
LIBFT	= ./libft

${NAME}:${OBJS} 
		make bonus -C ${LIBFT}
		gcc -g ${OBJS} ${LIBFT}/libft.a ${LIB} -o so_long
	
all:	${NAME} bonus

clean:
		${RM} ${OBJS}
		make clean -C ${LIBFT}

fclean:	clean
		${RM} ${NAME}
		make fclean -C ${LIBFT}
		
re: 	fclean all

.PHONY: all clean fclean re bonus 