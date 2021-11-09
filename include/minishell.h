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
{	char	*cmd;
	pid_t	parent;
	pid_t	child;
	int		child_exist;
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

// liste chainee redirection
typedef struct s_redir t_redir;
struct s_redir
{
	int		std_redir; //en fonction du type de sortie 
	t_redir	*next;
};

// liste chainee pour stocker cmds
typedef struct s_cmd t_cmd;
struct s_cmd
{
	int		nb; // numero de la cmd dans l'ordre d'arrivee
	int		cpy_nb;
	char	*fd; //nom du fd
	char	*cmd; // ex echo
	char	*spec; // ex -n
	char	*msg; // ex coucou
	int 	std; // en fonction du type de sortie 0 ou 1 ou -1
	char	*path; // nom du path
	t_redir	*redir;
	t_cmd	*next;
};

// // gestion des tokens (sq et dq)
// typedef struct s_token	t_token;
// struct	s_token
// {
// 	int		start_sq;
// 	int		end_sq;
// 	int		start_dq;
// 	int		end_dq;
// 	t_token	*next;
// };

// struct recuperant les cmds envoyees par l'user
typedef struct s_arg t_arg;
struct	s_arg
{
	//char	*arg;
	char	**cmds;
	int		i_cpy;
	int		count;
	int		count_quote;
	int		count_quotes;
	int		start;
	int		quote;
	int		pos_i;
	int		n;
	char	*spec_n;
	char	*tmp;
};

typedef struct s_env
{
	char **env;
	char **export;
} 				t_env;

int		main(int ac, char **av, char **envp);
char	*readline(const char *prompt);
t_list	*ft_get_env(t_list *env, char **envp);

// init
char	*ft_init_env(char **envp, t_list *env, int count);
void	ft_init_arg(t_arg *cmd, char *str);
int		ft_init_cmd(t_cmd **cmd, t_arg *arg);

// parsing
t_cmd	*ft_launch_parser(char *str, char **envp, t_cmd **cmd);
int		ft_get_arg(char *str, t_arg *arg);

// parse arguments
void	ft_count_arg(char *str, t_arg *arg);
void	ft_stock_arg(t_arg *arg, char *str);
char	*ft_parse_arg(char *str, int i, t_arg *arg);
int		ft_check_char(char *str, int i, int c, t_arg *arg);
void	ft_char(t_arg *arg, int c, char s, int nb);
char	*ft_nosep(int i, char *str, t_arg *arg);
int		ft_check_args(t_arg *arg);

// parse cmds
t_cmd	*ft_get_cmd(t_arg *arg, t_cmd **cmd);
t_cmd	*ft_parse_cmd(t_arg *arg, char **cpy, t_cmd *cmd);
t_cmd	*ft_parse_echo(t_arg *arg, char **cpy, t_cmd *cmd);
char	*ft_check_n(char **cpy, int i, t_arg *arg);
t_cmd	*ft_parse_builtins(t_arg *arg, char **cpy, t_cmd *cmd);
t_cmd	*ft_parse_special(t_arg *arg, char **cpy, t_cmd *cmd);
t_cmd	*ft_parse_other(t_arg *arg, char **cpy, t_cmd *cmd);
int		ft_std(t_arg *arg, t_cmd *cmd, int i);

//parse msg
char	*ft_cpy_msg(t_arg *arg, char **cpy, int j, t_cmd *new);
int 	ft_which_cmd(char **cpy);
char	*ft_msg(t_arg *arg, int start, char *tmp);
char	*ft_search_msg(char **cpy, int j, t_arg *arg, char *tmp);
char	*ft_other_msg(t_arg *arg, int start, char *tmp);
char	*ft_which_nb(int start, char *tmp, t_arg *arg);
char	*ft_parse_msg(char *cpy, t_arg *arg);
char	*ft_sq(t_arg *arg, char *str, char *tmp);
char	*ft_dq(t_arg *arg, char *str, char *tmp);
char	*ft_cut_quote(char *str, int start, int end);
char	*ft_special_cat(char *str, char *tmp, int i, int ret);
char	*ft_retneg(int i, char *str, char *tmp, char *new);
char	*ft_retnoneg(int i, char *str, char *tmp, char *new);

// redir
//t_redir	*ft_redir(t_arg *arg, char **cpy, t_cmd *cmd, t_redir **redir);
t_cmd	*ft_redir(t_arg *arg, char **cpy, t_cmd *cmd);

// utils
void	rm_split(char **split);
char	**ft_strsplit_s(char const *s, char c);
char	*transform_str(char *str, char **envp);
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
void	unset(char **envp, char *var);
void	export_sort(char **value, int len);
void	free_env(char **env);
char	**re_alloc(char **env);
int		add_env_variable(char ***env, char *var);
int		copy_env(char **envp, t_env *env);
int		get_env_lenght(char **env);
int		export(char **envp, char *path, char **argv);
int		get_fd(char *path);
int		echo(char *str, char *path, int flag_n);
int		env(char **envp, char *path);
int		pwd(char *path);
int		cd(char **env, char *path);

#endif