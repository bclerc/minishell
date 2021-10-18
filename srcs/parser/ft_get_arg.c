#include "minishell.h"

void	ft_get_arg(char *str)
{
	t_arg	arg;

	ft_init_arg(&arg, str);
	ft_count_arg(str, &arg);
	ft_stock_arg(&arg, str);
	//ft_free_arg(&arg);
}

void	ft_stock_arg(t_arg *arg, char *str)
{
	int	c;
	int start;
	int	i;
	char *tmp;

	c = 0;
	start = 0;
	i = 0;
	arg->cmds = malloc(sizeof(char *) * (arg->count + 1));
	if (!arg->cmds)
		return ;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>' || str[i] == '|')
		{
			arg->cmds[c] = ft_parse_cmds(str, i, start);
			printf("arg->cmds[%d] = %s start = %d\n", c, arg->cmds[c], start);
			c++;
			i = ft_check_char(str, i, c, arg);	
			start = i;
			printf("arg->cmds[%d] = %s start = %d\n", c, arg->cmds[c], start);
			c++;
		}
		i++;
	}
	printf("c2 = %d count2 = %d\n", c, arg->count);
	if (c != arg->count)
		arg->cmds[c] = ft_nosep(i, start, str, arg);
	printf("cmds = %s\n", arg->cmds[c]);
	start = 0;
}

void	ft_count_arg(char *str, t_arg *arg)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '>' && str[i + 1] == '>') || 
			(str[i] == '<' && str[i + 1] == '<'))
		{
			arg->count++;
			i++;
			if (str[i])
				arg->count++;
		}
		else if	(str[i] == '>' || str[i] == '<' || str[i] == '|')
		{
			arg->count++;
			if (str[i + 1])
				arg->count++;
		}	
		i++;
	}
	if (i == 0)
		arg->count = 0;
	printf("count = %d\n", arg->count);
}

void	ft_init_arg(t_arg *arg, char *str)
{
	ft_bzero(arg, sizeof(t_arg));
	if (str)
		arg->count = 1;
}

int	ft_check_cmds(t_arg *arg)
{
	int	i;
	int	j;
	
	i = 0;
	while (arg->cmds[i])
	{
		j = 0;
		while (arg->cmds[i][j])
		{
			if (arg->cmds[i][j] == '\'')
				arg->count_quote++;
			else if (arg->cmds[i][j] == '"')
				arg->count_quotes++;
			j++;
		}
		if (arg->count_quote % 2 != 0 || arg->count_quote % 2 != 0)
			return (ft_print("Error : There is an odd number of quotes\n", 1));
		i++;
	}
	return (0);
}
