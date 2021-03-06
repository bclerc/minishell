/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 11:00:59 by asgaulti          #+#    #+#             */
/*   Updated: 2022/01/14 17:16:26 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <dirent.h>

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
	char			*value;
	struct s_env	*next;	
}						t_env;

typedef struct s_split
{
	char			value;
	struct s_split	*next;

}				t_split;

typedef struct s_core
{
	t_env	*env;
	pid_t	parent;
	pid_t	child;
	int		child_exist;
}						t_core;

extern t_core			*g_core;

//liste chainee pour stocker env
typedef struct s_list	t_list;

struct s_list
{
	char	*content;
	t_list	*next;
};

// liste chainee redirection
typedef struct s_redir	t_redir;
struct s_redir
{
	int		std_redir;
	int		redir_std_in;
	int		redir_std_out;
	int		redir_std_pipe;
	char	*redir_msg;
	char	*fd_in;
	char	*fd_out;
	t_redir	*next;
};

// liste chainee pour stocker cmds
typedef struct s_cmd	t_cmd;

struct s_cmd
{
	int		cpy_nb;
	int		builtin;
	char	*cmd;
	char	*spec;
	char	*msg;
	int		std;
	t_redir	*redir;
	t_cmd	*prev;
	t_cmd	*next;
};

// struct recuperant les cmds envoyees par l'user
typedef struct s_arg	t_arg;
struct	s_arg
{
	char	**cmds;
	int		i_cpy;
	int		j;
	int		count;
	int		count_quote;
	int		count_quotes;
	int		start;
	int		quote;
	int		pos_i;
	int		n;
	int		q;
	int		c;
	int		i;
	int		spec_n;
	int		sp;
	int		std;
	char	*tmp;
};

typedef struct s_data	t_data;

struct s_data
{
	char	*fd_in;
	char	*msg;
	int		std_in;
};

int		main(int ac, char **av, char **envp);
char	*readline(const char *prompt);
t_list	*ft_get_env(t_list *env, char **envp);

// init
char	*start_prompt(void);
char	*ft_init_env(char **envp, t_list *env, int count);
void	ft_init_arg(t_arg *cmd, char *str);
int		ft_init_cmd(t_cmd **cmd, t_arg *arg);
int		ft_init_redir(t_redir *redir);
t_data	*ft_init_data(t_data *data);

// parsing
t_cmd	*ft_launch_parser(char *str, t_cmd **cmd);
int		ft_get_arg(char *str, t_arg *arg);
int		ft_no(char *str);

// parse arguments
int		ft_quotes(char *str, t_arg *arg);
int		ft_increase_quote(char *str, int i);
int		ft_count1(char *str, int i, t_arg *arg);
void	ft_count2(char *str, int i, t_arg *arg);
int		ft_count_arg(char *str, t_arg *arg);
int		ft_stock_arg(t_arg *arg, char *str);
int		ft_stock_i(char *str, int i);
char	*ft_parse_arg(char *str, int i, t_arg *arg);
int		ft_check_char(char *str, int i, int c, t_arg *arg);
int		ft_check_chevron(char *str, int i, int c, t_arg *arg);
void	ft_char(t_arg *arg, int c, char s, int nb);
char	*ft_nosep(int i, char *str, t_arg *arg);
int		ft_begin_chevron(char *str, int i, int size, t_arg *arg);
int		ft_begin_util(char *str, int i, int size, t_arg *arg);
void	ft_util_stockarg(t_arg *arg);
int		ft_special_chev(t_arg *arg, char *str);
//int		ft_check_args(t_arg *arg);

// parse cmds
t_cmd	*ft_get_cmd(t_arg *arg, t_cmd **cmd);
int		ft_cmd_i(t_arg *arg, int i);
char	*ft_cpy0(char *cpy, t_arg *arg);
int		ft_check_redir(t_arg *arg, int i);
char	*ft_cmd_quotes(char *cpy);
t_cmd	*ft_parse_cmd(t_arg *arg, char **cpy, t_cmd *cmd);
t_cmd	*ft_parse_echo(t_arg *arg, char **cpy, t_cmd *cmd);
t_cmd	*ft_fill_echo1(t_cmd *new, t_arg *arg, char **cpy);
t_cmd	*ft_fill_echo2(char **cpy, t_arg *arg, t_cmd *new);
int		ft_fill_echostd(t_arg *arg, t_cmd *new);

int		ft_check_n(char **cpy, int i, t_arg *arg, t_cmd *new);
t_cmd	*ft_parse_builtins(t_arg *arg, char **cpy, t_cmd *cmd);
t_cmd	*ft_fill_builtin(char **cpy, t_cmd *new, t_arg *arg);
t_cmd	*ft_fill_other(char **cpy, t_cmd *new, t_arg *arg);
t_cmd	*ft_cmd_builtin(t_cmd *cmd, t_cmd *tmp2, t_cmd *new);
t_cmd	*ft_parse_other(t_arg *arg, char **cpy, t_cmd *cmd);
void	ft_fill_std(t_arg *arg, t_cmd *new);
int		ft_std(t_arg *arg, int i);
void	ft_spec_out(t_cmd *new, t_arg *arg);
void	ft_spec_in(t_cmd *new, t_arg *arg);
t_cmd	*ft_check_spec(t_cmd **cmd);
int		ft_special_exist(t_arg *arg);
t_cmd	*ft_chevron(t_arg *arg, t_cmd *cmd);

//parse msg
char	*ft_cpy_msg(t_arg *arg, char **cpy, int j, t_cmd *new);
int		ft_which_cmd(char **cpy);
char	*ft_msg(t_arg *arg, int start, char *tmp);
char	*ft_search_msg(char **cpy, int j, t_arg *arg, char *tmp);
char	*ft_other_msg(t_arg *arg, int start, char *tmp);
char	*ft_which_nb(int start, char *tmp, t_arg *arg);
char	*ft_parse_msg(char *cpy, t_arg *arg);
char	*ft_check_quotes(char *str, t_arg *arg, char *tmp, int size);
char	*ft_check_tmp(char *tmp, int pos_st, char *str, int i);
char	*ft_sq(t_arg *arg, char *str, char *tmp);
char	*ft_dq(t_arg *arg, char *str, char *tmp);
int		ft_i_quotes(int i, t_arg *arg, char *str);
int		ft_i_quote(int i, t_arg *arg, char *str);
char	*ft_cut_quote(char *str, int start, int end);
char	*ft_special_cat(char *str, char *tmp, int i, int ret);
char	*ft_special_cat_export(char *str, char *tmp, int i, int ret);
char	*ft_retneg(int i, char *str, char *tmp, char *new);
char	*ft_retnoneg(int i, char *str, char *tmp, char *new);
char	*ft_cut_quote_export(char *str, int start, int end);

// Environnement
t_split	*change_value(t_split *start, t_split *end, int status);
t_split	*get_str(char *str, int len);
void	add_value(t_split *src, t_split *dst);
char	*to_string(t_split *split);
char	**env_to_char(void);
void	fill_env(void);
int		get_env(char **envp);
int		del_env_variable(char *var);
void	del_env(void);

// redir
//t_redir	*ft_redir(t_arg *arg, char **cpy, t_cmd *cmd, t_redir **redir);
t_cmd	*ft_redir(t_cmd *cmd);
int		ft_exist(t_cmd *tmp);
t_cmd	*ft_isredir(int exist, t_cmd *tmp, t_cmd *cmd, t_redir *redir);
t_cmd	*ft_fillin(t_cmd *cmd, t_redir *redir);
t_cmd	*ft_util_in1(t_cmd *cmd);
t_cmd	*ft_util_in2(t_redir *redir, t_cmd *cmd, char *fd_in, int std_in);
t_cmd	*ft_fillout(t_cmd *cmd, t_redir *redir);
t_redir	*ft_create_out(t_cmd *cmd, t_redir *redir);
void	ft_util_out(t_redir *new, t_cmd *cmd);
t_cmd	*ft_fillinout(t_cmd *tmp, t_redir *redir, char *in, int std_in);
t_cmd	*ft_inout(t_cmd *tmp, t_cmd *cmd, t_redir *redir);
t_cmd	*ft_in(t_data *data, t_cmd *tmp, t_redir *redir);
t_redir	*ft_out(t_cmd *cmd, t_redir *redir, char *msg);
t_data	*ft_check_in(t_cmd *tmp, t_data *data);
t_cmd	*ft_util_inout(t_data *data, t_cmd *tmp, t_redir *redir);

int		ft_recup_in(char **fd_in, t_cmd *tmp, int std_in);
t_redir	*ft_create_out2(char *in, int std_in, t_cmd *cmd, t_redir *redir);

t_redir	*ft_create_redir(t_cmd *tmp, t_cmd *cmd, t_redir *redir);
t_redir	*ft_fillfd(t_cmd *cmd, t_redir *new);
t_redir	*ft_left(t_cmd *cmd, t_redir *redir);
t_redir	*ft_newredir(t_redir *new, int i);
int		mul_redir(t_cmd *cmd);
// utils

int		is_in_set(char c, char *set);
int		random_char(void);
void	m_exit(t_cmd *cmd, int reason, char *function);
void	change_env(char	**new_env);
int		get_env_length(char **env);
int		ft_havechr(char *str, char c);
void	rm_split(char **split);
char	*fill(const char *str, char *set, int *i);
void	replace_var(char save, char **s, int status);
char	**ft_strsplit_s(const char *str, char *set, int status);
char	*transform_str(char *str, int status);
int		ft_print(char *str, int res);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **alst, t_list *new);
char	*get_env_variable(char *var);
char	*get_promps(void);
void	ft_free_arg(t_arg *arg);
char	*ft_sep(t_arg *arg, int i, char c, int count);
char	*ft_strtrim(char const *s1, char const *set);
int		is_eof(char *s);
void	ft_lstdelone(t_cmd *lst, void (*del)(t_cmd *));

// pipe
t_cmd	*dup_cmd(t_cmd *cmd);
int		get_pipe_count(t_cmd *cmd);
int		m_pipe(t_cmd *cmd, int status);
int		close_fd(int *tab_fd, int nb_pipes);
int		open_pipe(int *tab_fd, int nb_pipes);
int		fork_cmd(int *pipes, t_cmd *cmd, int nbpipe, int status);
int		is_forkable(t_cmd *cmd);
int		set_in_out(int *pipes, t_cmd *cmd, int i, int nbpipes);

// execution
int		execute_commands(t_cmd *cmd, int status);
char	**get_argv(t_cmd *cmd);
char	*heredoc(t_cmd *cmd);
// built-in function
void	export_sort(char **value, int len);
void	free_env(char **env);
char	**re_alloc(char **env);
int		unset(char *var);
int		builtin_exit(t_cmd *cmd, int status);
int		add_env_variable(char *var);
int		get_env_length(char **env);
int		export(char *path, char *argv);
int		have_access(char *home, char *path);
int		get_fd(char *path, int append);
int		echo(t_cmd *cmd);
int		env(char *path);
int		pwd(char *path);
int		cd(char *path);
t_cmd	*dupp_cmd(t_cmd *cmd);

#endif