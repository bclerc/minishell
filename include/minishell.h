#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <signal.h>

# define BUF_SIZE 42

typedef struct s_core
{
	pid_t	main_parent;
	pid_t	main_child;
	pid_t	exec_chill;
	int		fd[2];
	int		status;
}				t_core;

extern t_core core;
//liste chainee pour stocker env
typedef struct s_list t_list;
struct s_list
{
	char	*content;
	t_list	*next;
};

// liste chainee pour stocker cmds
typedef struct s_cmd t_cmd;
struct s_cmd
{
	int		nb; // numero de la cmd dans l'ordre d'arrivee
	char	*arg; // ex echo
	char	*spec; // ex -n
	char	*msg; // ex coucou
	int 	std; // en fonction du type de sortie 0 ou 1 ou -1
	t_cmd	*next;
};

// struct recuperant les cmds envoyees par l'user
typedef struct s_arg t_arg;
struct	s_arg
{
	//char	*arg;
	char	**cmds;
	int		count;
	int		count_quote;
	int		count_quotes;
};

typedef struct s_env
{
	char **env;
	char **export;
} 				t_env;

int		main(int ac, char **av, char **envp);
char	*ft_init_env(char **envp, t_list *env, int count);
char	*readline(const char *prompt);
t_list	*ft_get_env(t_list *env, char **envp);

// parsing
void	ft_get_arg(char *str);
void	ft_init_arg(t_arg *cmd, char *str);
int		parser(char *str, char **envp);
int		ft_check_cmds(t_arg *cmd);
int		ft_check_quotes(t_arg *cmd);
int		ft_get_cmd(t_arg *arg);
void	ft_count_arg(char *str, t_arg *arg);
int		ft_parse_echo(t_arg *arg, t_cmd *cmd, int i);
int		ft_check_n(t_arg *arg, t_cmd *cmd, int i);
int		ft_echo_msg(t_arg *arg, t_cmd *cmd, int i);
void	ft_stock_arg(t_arg *arg, char *str);
char	*ft_parse_pipe(char *str, int i, int start);
//char	*ft_parse_cmds(char *str, int i, int start);

// utils

int		ft_print(char *str, int res);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **alst, t_list *new);
char	*get_env_variable(char *var, char **envp);
char	*get_promps(char **envp);
void	ft_free_arg(t_arg *arg);
char	*ft_sep(t_arg *arg, int i, char c, int count);
char	*ft_strtrim(char const *s1, char const *set);
// gnl
int		get_next_line(int fd, char **line);
char	*ft_get_static(char *str, char buf[BUF_SIZE], int len);
char	*ft_write_line(char *str, char **line);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);

// execution
int	execute_commands(char *args, char **envp, char *path);

// built-in function
int		copy_env(char **envp, t_env *env);
char	**re_alloc(char **env);
void	export_sort(char **value, int len);
void	free_env(char **env);
int 	add_env_variable(t_env *env, char *var);
int		get_env_lenght(char **env);
int		export(char **envp, char *path);
int		get_fd(char *path);
int		unset(char **envp, char *var);
int		echo(char *str, char *path, int flag_n);
int		env(char **envp, char *path);
int		pwd(char *path);
int		cd(char **env, char *path);

#endif