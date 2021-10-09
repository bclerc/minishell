#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>

# define BUF_SIZE 42

typedef struct s_list t_list;
struct s_list
{
	char	*content;
	t_list	*next;
};

typedef struct s_cmd t_cmd;
struct	s_cmd
{
	//char	*arg;
	char	**cmds;
	int		count_quote;
	int		count_quotes;
};

int		main(int ac, char **av, char **envp);
char	*ft_init_env(char **envp, t_list *env, int count);
char	*readline(const char *prompt);
t_list	*ft_get_env(t_list *env, char **envp);

// parsing
void	ft_get_cmd(char *str);
void	ft_init_cmd(t_cmd *cmd);
int		ft_check_cmds(t_cmd *cmd);
int		ft_check_quotes(t_cmd *cmd);

// utils
int		ft_print(char *str, int res);
int		ft_strlen(char *str);
char	*ft_strdup(char *s1);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_bzero(void *s, size_t n);
char	**ft_split(char const *s, char c);

// gnl
int		get_next_line(int fd, char **line);
char	*ft_get_static(char *str, char buf[BUF_SIZE], int len);
char	*ft_write_line(char *str, char **line);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);

#endif