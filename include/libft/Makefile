#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by  bclerc           #+#    #+#              #
#    Updated: 2019/11/13 16:08:59 by bclerc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


############## COLORS ##################
_WHITE=$ \x1b[37m
_BLUE=$ \x1b[36m
_GREEN=$ \033[1;32m
_GREY=$ \x1b[33m
_RED=$ \x1b[31m

############## FLAGS ##################

NAME= libft.a
CC = gcc
LDFLAGS = -Llibft
LDLIBS = -lft
CFLAGS =

############## FILES ##################

SRC= 		ft_memset.c \
			ft_bzero.c \
			ft_strisdigit.c \
			ft_memcpy.c \
			ft_swap.c \
			ft_memccpy.c \
			ft_isupper.c \
			ft_putnstr.c \
			ft_strsave.c \
			ft_strcdup.c \
			ft_memmove.c \
			ft_memcmp.c \
			ft_memchr.c	 \
			ft_strlen.c	\
			ft_strdup.c \
			ft_strcpy.c \
			ft_strncpy.c \
			ft_strcat.c \
			ft_strncat.c \
			ft_strchr.c \
			ft_abs.c \
			ft_itoa.c \
			ft_strrchr.c \
			ft_strstr.c \
			ft_strcmp.c \
			ft_strncmp.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isascii.c \
			ft_isalnum.c \
			ft_isprint.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_atoi.c \
			ft_strlcat.c \
			ft_memalloc.c \
			ft_memdel.c \
			ft_strnew.c \
			ft_strnstr.c \
			ft_strdel.c \
			ft_strclr.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strequ.c \
			ft_strnequ.c \
			ft_strsub.c \
			ft_strndup.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_putchar.c \
			ft_putchar_fd.c \
			ft_putstr.c \
			ft_putstr_fd.c \
			ft_putnbr.c \
			ft_putnbr_fd.c \
			ft_putendl.c \
			ft_putendl_fd.c \
			ft_strsplit.c

############## PATH ##################

OBJECTS	= $(SRC:.c=.o)

.PHONY: clean fclean re all

all: $(NAME)
$(NAME): $(OBJECTS)
		@echo "[OK] Tous les objets sont generes\r"
		@ar rc $(NAME) $(OBJECTS) || printf "\n[ERREUR] Une est erreur est survenue $(NAME)\n"
		@ranlib $(NAME)
		@echo "[OK] Compilation de $(NAME)"

%.o: %.c
		@$(CC) $(CFLAGS)  -o $@ -c $< && printf "[OK] Generation de %-50s\r" "$@" || \
		 (echo "[ERREUR] Une est erreur est survenue sur $<, $(NAME) non compilé(e)\n" && $(MAKE) fclean && exit 1)

clean:
		@rm -rf $(OBJECTS)
		@echo "[OK] Supression de tous les objets"

fclean: clean
		@rm -rf $(NAME) $(EXE)
		@echo "[OK] Supression de $(NAME)"
		@echo "[OK] Supression de tous les fichiers"

re: fclean all
		@echo "[OK] Fini "
