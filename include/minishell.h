#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

# define BUF_SIZE 42
# define REDIR_OUT 2
# define REDIR_APPEND_OUT 3
# define REDIR_IN 4
# define REDIR_APPEND_IN 5

# define M_EXIT_MALLOC_ERROR 1
# define M_EXIT_SUCCESS 2
# define M_EXIT_FORK 3
typedef struct s_env
{

	char		*value;
	struct s_env *next;	

}				t_env;

typedef struct s_core
{
	char	*cmd;
	char	**envp;
	t_env	*env;
	pid_t	parent;
	pid_t	child;
	int		child_exist;
	int		fd[2];
	int		status;
}				t_core;

extern t_core *core;

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
	//char	*cmd_redir;
	char	*fd_in;
	char	*fd_out;
	t_redir	*next;
};

// liste chainee pour stocker cmds
typedef struct s_cmd t_cmd;
struct s_cmd
{
	int		cpy_nb;
	int		builtin; //1 builtin 0 pas builtin
	char	*cmd; // ex echo
	char	*spec; // ex -n
	char	*msg; // ex coucou
	int 	std; // en fonction du type de sortie 0 ou 1 ou -1
	t_redir	*redir;
	t_cmd	*previous;
	t_cmd	*next;
};

// struct recuperant les cmds envoyees par l'user
typedef struct s_arg t_arg;
struct	s_arg
{
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

int		main(int ac, char **av, char **envp);
char	*readline(const char *prompt);
t_list	*ft_get_env(t_list *env, char **envp);

// init
char	*ft_init_env(char **envp, t_list *env, int count);
void	ft_init_arg(t_arg *cmd, char *str);
int		ft_init_cmd(t_cmd **cmd, t_arg *arg);

// parsing
t_cmd	*ft_launch_parser(char *str, t_cmd **cmd);
int		ft_get_arg(char *str, t_arg *arg);

// parse arguments
void	ft_count_arg(char *str, t_arg *arg);
int		ft_stock_arg(t_arg *arg, char *str);
char	*ft_parse_arg(char *str, int i, t_arg *arg);
int		ft_check_char(char *str, int i, int c, t_arg *arg);
void	ft_char(t_arg *arg, int c, char s, int nb);
char	*ft_nosep(int i, char *str, t_arg *arg);
int		ft_check_args(t_arg *arg);

// parse cmds
t_cmd	*ft_get_cmd(t_arg *arg, t_cmd **cmd);
int		ft_check_redir(t_arg *arg, int i);
t_cmd	*ft_parse_cmd(t_arg *arg, char **cpy, t_cmd *cmd);
t_cmd	*ft_parse_echo(t_arg *arg, char **cpy, t_cmd *cmd);
int		ft_check_n(char **cpy, int i, t_arg *arg, t_cmd *new);
t_cmd	*ft_parse_builtins(t_arg *arg, char **cpy, t_cmd *cmd);
t_cmd	*ft_parse_other(t_arg *arg, char **cpy, t_cmd *cmd);
void	ft_fill_std(t_arg *arg, t_cmd *new);
int		ft_std(t_arg *arg, int i);
void	ft_spec_out(t_cmd *new, t_arg *arg);
void	ft_spec_in(t_cmd *new, t_arg *arg);
t_cmd	*ft_check_spec(t_cmd **cmd);

//parse msg
char	*ft_cpy_msg(t_arg *arg, char **cpy, int j, t_cmd *new);
int		ft_which_cmd(char **cpy);

// Environnement
char	**env_to_char();
int		getEnv(char **envp);
int		del_env_variable(char *var);

char	*ft_msg(t_arg *arg, int start, char *tmp);
char	*ft_search_msg(char **cpy, int j, t_arg *arg, char *tmp);
char	*ft_other_msg(t_arg *arg, int start, char *tmp);
char	*ft_which_nb(int start, char *tmp, t_arg *arg);
char	*ft_parse_msg(char *cpy, t_arg *arg);
char	*ft_check_quotes(char *str, t_arg *arg, char *tmp, int size);
char	*ft_check_tmp(char *tmp, int pos_st, char *str, int i);
char	*ft_sq(t_arg *arg, char *str, char *tmp);
char	*ft_dq(t_arg *arg, char *str, char *tmp);
char	*ft_cut_quote(char *str, int start, int end);
char	*ft_special_cat(char *str, char *tmp, int i, int ret);
char	*ft_retneg(int i, char *str, char *tmp, char *new);
char	*ft_retnoneg(int i, char *str, char *tmp, char *new);

// redir
//t_redir	*ft_redir(t_arg *arg, char **cpy, t_cmd *cmd, t_redir **redir);
t_cmd	*ft_redir(t_cmd *cmd);
t_redir	*ft_create_redir(t_cmd *tmp, t_cmd *cmd, t_redir *redir);
t_redir	*ft_fillfd(t_cmd *cmd, t_redir *new);
t_redir	*ft_left(t_cmd *cmd, t_redir *redir);
t_redir	*ft_newredir(t_redir *new, int i);

// utils
void    m_exit(t_cmd *cmd, int reason, char *function);
void	change_env(char	**new_env);
int		get_env_length(char **env);
int		ft_havechr(char* str, char c);
void	rm_split(char **split);
char	**ft_strsplit_s(char const *s, char c);
char	*transform_str(char *str);
int		ft_print(char *str, int res);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **alst, t_list *new);
char	*get_env_variable(char *var);
char	*get_promps(void);
void	ft_free_arg(t_arg *arg);
char	*ft_sep(t_arg *arg, int i, char c, int count);
char	*ft_strtrim(char const *s1, char const *set);

// pipe
int		get_pipe_count(t_cmd *cmd);
int		m_pipe(t_cmd *cmd);
int		close_fd(int *tab_fd, int nb_pipes);
int		open_pipe(int *tab_fd, int nb_pipes);

// execution
int		execute_commands(t_cmd *cmd);
char	**get_argv(t_cmd *cmd);

// built-in function
void	export_sort(char **value, int len);
void	free_env(char **env);
char	**re_alloc(char **env);
int		unset(char *var);
int		add_env_variable(char *var);
int		get_env_length(char **env);
int		export(char *path, char *argv);
int		get_fd(char *path);
int		echo(char *str, char *path, int flag_n);
int		env(char *path);
int		pwd(char *path);
int		cd(char *path);

#endif