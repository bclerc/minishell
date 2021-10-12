# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 16:27:13 by asgaulti          #+#    #+#              #
#    Updated: 2021/10/12 10:40:42 by bclerc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRCS	=	main.c ft_init.c parser/ft_get_cmd.c parser/ft_gnl.c \
			utils/ft_split.c utils/ft_utils_gnl.c utils/ft_utils.c \
			built-in/cd/cd.c \
			built-in/echo/echo.c \
			built-in/env/env.c \
			built-in/export/export.c \
			built-in/export/export_utils.c \
			built-in/pwd/pwd.c \
			built-in/utils.c \
			built-in/unset/unset.c


PATH_SRCS = srcs/

OBJS	=	${addprefix ${PATH_SRCS}, ${SRCS:.c=.o}}

CC		=	clang
#clang-9 
RM		=	rm -f
CFLAGS	=	
CFLAGS	+= -g3 -fsanitize=address

INCL	=	include

.c.o:
			${CC} ${CFLAGS} -I${INCL} -g -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			${CC} ${CFLAGS} ${LFLAGS} ${OBJS} -o ${NAME} -lreadline

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}
					
re:			fclean all

.PHONY:		all clean fclean re