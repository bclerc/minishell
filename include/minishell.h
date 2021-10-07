#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_env
{
	char	**env;
}				t_env;

int		main(int ac, char **av, char **envp);
char	*ft_init_env(char **envp, t_env *env, int count);
char	*readline(const char *prompt);

// utils
int		ft_print(char *str, int res);
int		ft_strlen(char *str);
char	*ft_strdup(char *s1);

#endif