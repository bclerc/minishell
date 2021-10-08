#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_list t_list;
struct s_list
{
	char	*content;
	t_list	*next;
};

int		main(int ac, char **av, char **envp);
char	*ft_init_env(char **envp, t_list *env, int count);
char	*readline(const char *prompt);
t_list	*ft_get_env(t_list *env, char **envp);

// utils
int		ft_print(char *str, int res);
int		ft_strlen(char *str);
char	*ft_strdup(char *s1);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **alst, t_list *new);

#endif