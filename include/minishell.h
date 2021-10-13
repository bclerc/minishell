#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <readline/history.h>
# include <sys/stat.h>

# define BUF_SIZE 42

enum	e_cmd
{
	_cd,
	_echo,
	_env,
	_export,
	_pwd,
	_unset,
	m_exit

};

//liste chainee pour stocker env
typedef struct s_list t_list;
struct s_list
{
	char	*content;
	t_list	*next;
};

// struct recuperant les cmds envoyees par l'user
typedef struct s_cmd t_cmd;
struct	s_cmd
{
	//char	*arg;
	char	**cmds;
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
void	ft_get_cmd(char *str);
void	ft_init_cmd(t_cmd *cmd);
int		parser(char *str, char **envp);
int		ft_check_cmds(t_cmd *cmd);
int		ft_check_quotes(t_cmd *cmd);

// utils

int     ft_strcmp(const char *str1, const char *str2);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		ft_print(char *str, int res);
int		ft_strlen(char *str);
char	*ft_strdup(char *s1);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_bzero(void *s, size_t n);
char	**ft_split(char const *s, char c);
char	*get_env_variable(char *var, char **envp);
char	*get_promps(char **envp);

// gnl
int		get_next_line(int fd, char **line);
char	*ft_get_static(char *str, char buf[BUF_SIZE], int len);
char	*ft_write_line(char *str, char **line);
char	*ft_strjoin(char *s1, char *s2);
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