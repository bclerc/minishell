NAME = minishell
PROJECT_NAME = minishell

SOURCES_FOLDER = ./
INCLUDES_FOLDER = include

OBJECTS_FOLDER = ./

LIBS = libft

SOURCES =	srcs/main.c \
			srcs/ft_init.c \
			srcs/utils/envgeter.c \
			srcs/parser/ft_get_arg.c\
			srcs/parser/ft_gnl.c \
			srcs/utils/ft_utils_gnl.c srcs/utils/ft_utils.c \
			srcs/parser/ft_parse_arg.c \
			srcs/parser/ft_parser.c \
			srcs/parser/ft_get_cmd.c \
			srcs/parser/ft_parse_echo.c \
			srcs/parser/ft_parse_builtins.c \
			srcs/parser/ft_msg.c \
			srcs/parser/ft_parse_msg.c \
			srcs/utils/ft_strcmp.c \
			srcs/utils/ft_strsplit_space.c \
			srcs/utils/ft_strncmp.c \
			srcs/utils/prompts.c \
			srcs/utils/env_variable.c \
			srcs/utils/ft_free.c \
			srcs/utils/ft_utils_parsing.c \
			srcs/utils/ft_strtrim.c \
			srcs/commands/commands.c \
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
CFLAGS =  -g3 -g
CC = gcc

.PHONY: all re clean fclean libft force doclean

all: $(NAME)

$(LIBS):
	@printf "All objects for $(PROJECT_NAME) where successfully created.\n"
	@printf "\n-------- Libft --------\n"
	@make -s -C include/$(@)
	@printf "\n-------- $(PROJECT_NAME) --------\n"


$(NAME): $(OBJECTS) $(LIBS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) -L$(INCLUDES_FOLDER) -Linclude/libft -lft -lreadline
	@printf "$(NAME) successfully compiled. ✓\n"

force: $(OBJECTS)
	@printf "$All objects for $(PROJECT_NAME) where successfully created.\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) -g
	@printf "$(NAME) successfully compiled. ✓\n"

%.o: %.c
	@$(CC) $(FLAGS) -I$(INCLUDES_FOLDER) -c $< -o $@ -Iinclude
	@printf "Creating %-30s ✓\r" "$@"

clean:
	@make -C include/$(LIBS) clean
	@rm -f $(OBJECTS)
	@printf "$(PROJECT_NAME) Removed all objects.\n"

fclean: clean
	@make -C include/$(LIBS) fclean
	@rm -f $(NAME)
	@printf "$(PROJECT_NAME) Removed $(NAME).\n"

doclean: all clean

re: fclean all