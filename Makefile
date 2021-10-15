# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 16:27:13 by asgaulti          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2021/10/14 11:03:23 by bclerc           ###   ########.fr        #
=======
#    Updated: 2021/10/15 10:52:52 by user42           ###   ########.fr        #
>>>>>>> 434b923574d4ba368891cc9c1deb2acd4f59d30d
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRCS	=	main.c ft_init.c parser/ft_get_arg.c parser/ft_gnl.c \
			utils/ft_split.c utils/ft_utils_gnl.c utils/ft_utils.c \
			parser/parser.c \
			parser/ft_parse_echo.c \
			utils/ft_strcmp.c \
			utils/ft_itoa.c \
			utils/ft_strncmp.c \
			utils/prompts.c \
			utils/env_variable.c \
			utils/ft_free.c \
			utils/ft_utils_parsing.c \
			utils/ft_strtrim.c \
			commands/commands.c \
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
CFLAGS	+= -g3

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