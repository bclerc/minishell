# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/31 11:16:20 by asgaulti          #+#    #+#              #
#    Updated: 2022/01/09 19:14:59 by bclerc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
PROJECT_NAME = minishell

SOURCES_FOLDER = ./
INCLUDES_FOLDER = include

OBJECTS_FOLDER = ./

LIBS = libft
PURPLE = \033[1;35m
CYAN = \033[1;36m
GREEN = \033[1;32m

SOURCES =	srcs/main.c \
			srcs/ft_init.c \
			srcs/utils/envgeter.c \
			srcs/parser/ft_get_arg.c\
			srcs/utils/ft_utils.c \
			srcs/parser/ft_parse_arg.c \
			srcs/parser/ft_parser.c \
			srcs/parser/ft_get_cmd.c \
			srcs/parser/ft_parse_echo.c \
			srcs/parser/ft_parse_builtins.c \
			srcs/parser/ft_msg.c \
			srcs/parser/ft_parse_msg.c \
			srcs/parser/ft_spec.c \
			srcs/parser/ft_redir.c \
			srcs/parser/ft_inandout.c \
			srcs/utils/ft_strsplit_space.c \
			srcs/utils/prompts.c \
			srcs/utils/env_variable.c \
			srcs/utils/ft_free.c \
			srcs/utils/ft_utils_parsing.c \
			srcs/utils/ft_strtrim.c \
			srcs/utils/ft_util_parsemsg.c \
			srcs/utils/exit.c \
			srcs/utils/ft_utils_redir.c \
			srcs/utils/ft_utils_cmd.c \
			srcs/utils/ft_utils_arg.c \
			srcs/utils/ft_utils_builtin.c \
			srcs/commands/commands.c \
			srcs/commands/commands_utils.c \
			srcs/commands/pipe.c \
			srcs/commands/pipe_utils.c \
			srcs/commands/redir_utils.c \
			srcs/built-in/cd/cd.c \
			srcs/built-in/echo/echo.c \
			srcs/built-in/env/env.c \
			srcs/built-in/export/export.c \
			srcs/built-in/export/export_utils.c \
			srcs/built-in/pwd/pwd.c \
			srcs/built-in/utils.c \
			srcs/built-in/unset/unset.c

OBJECTS = $(SOURCES:.c=.o)

FSANITIZE = -fsanitize=address
CFLAGS = -g3 

.PHONY: all re clean fclean libft force doclean

all: $(NAME)
$(LIBS):
	@printf "$(CYAN)Compiling $(PURPLE)$(PROJECT_NAME)$(CYAN) ... %-40s\n" " "
	@printf "$(CYAN)All objects for $(PURPLE)$(PROJECT_NAME) $(CYAN)where successfully created.\n"
	@printf "$(CYAN)\n-------- $(PURPLE)Libft$(CYAN) --------\n"
	@make --no-print-directory -s -C include/$(@)
	@printf "$(CYAN)\n-------- $(PURPLE)$(PROJECT_NAME)$(CYAN) --------\n"


$(NAME): $(OBJECTS) $(LIBS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) -L$(INCLUDES_FOLDER) -Linclude/libft -lft -lreadline
	@printf "$(PURPLE)$(NAME) $(CYAN)successfully compiled. $(GREEN)✓$(CYAN)\n"
force: $(OBJECTS)
	@printf "$(CYAN) All objectsfor $(PURPLE)$(PROJECT_NAME)$(CYAN) where successfully created.\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) -g
	@printf "$(PURPLE)$(NAME)$(CYAN) successfully compiled. $(CGREEN)✓$(CYAN)\n"

%.o: %.c
	@$(CC) $(CFLAGS) -I$(INCLUDES_FOLDER) -c $< -o $@ -Iinclude
	@printf "$(CYAN)Creating $(PURPLE)%-40s$(GREEN) ✓$(CYAN)\r" "$@"

clean:
	@make -s -C include/$(LIBS) clean
	@rm -f $(OBJECTS)
	@printf "$(PURPLE)$(PROJECT_NAME) $(CYAN)Removed all objects.\n"

fclean: clean
	@make -s -C include/$(LIBS) fclean
	@rm -f $(NAME)
	@printf "$(PURPLE)$(PROJECT_NAME) $(CYAN)Removed $(PURPLE)$(NAME)$(CYAN).\n"

doclean: all clean

re: fclean all