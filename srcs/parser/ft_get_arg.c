#include "minishell.h"

void	ft_get_arg(char *str)
{
	t_arg	arg;

	ft_init_arg(&arg, str);
	ft_count_arg(str, &arg);
	if (!arg.count)
	{
		ft_print("There is no command, try again!\n", -1);
		return ;
	}
	// arg.cmds = malloc(sizeof(char *) * arg.count);
	// if (!arg.cmds)
	// 	return ;
	ft_stock_arg(&arg, str);
	//ft_free_arg(&arg);
}

void	ft_stock_arg(t_arg *arg, char *str)
{
	int	c;
	int start;
	int	i;
	char *tmp;

//printf("count = %d\n", arg->count);
	c = 0;
	start = 0;
	i = 0;
	arg->cmds = malloc(sizeof(char *) * (arg->count + 1));
	if (!arg->cmds)
		return ;
	while (str[i])
	{
		if (str[i] == '|')
		{
			arg->cmds[c] = ft_parse_pipe(str, i, start);
			printf("arg->cmds[%d] = %s start = %d\n", c, arg->cmds[c], start);
			c++;
			ft_char(arg, c, '|', 1);
			start = i;
			printf("arg->cmds[%d] = %s start = %d\n", c, arg->cmds[c], start);
			c++;
		}
	/*	if (str[i] == '<' || str[i] == '>')
		{
			arg->cmds[c] = ft_parse_chevron(str, i, start);
			printf("arg->cmds[%d] = %s start = %d\n", c, arg->cmds[c], start);
			c++;
			start = i;
		}*/
		i++;
		printf("i = %d start = %d\n", i, start);
	}
	if (c != arg->count)
		arg->cmds[c] = ft_nosep(i, start, str, arg);
	printf("cmds = %s\n", arg->cmds[c]);
	start = 0;
}

/*char	*ft_parse_cmds(char *str, int i, int start)
{
	char	*tmp;
	int 	c;

	tmp = malloc(sizeof(char) * i);
	if (str[i] == '>')
	{
		if (str[i + 1] == '>')
		{
			tmp = ft_double_right(str, i, start);
		}
	}
	else if (str[i] == '<')
	{

	}
	return (tmp);
}*/

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
		}
		else if	(str[i] == '>' || str[i] == '<' || str[i] == '|')
			arg->count++;
		i++;
	}
	if (i == 0)
		arg->count = 0;
}
/*
void	ft_get_arg(char *str)
{
	int		i;
	t_arg	arg;

	i = 0;
	ft_init_arg(&arg);
	while (str[i])
	{
		arg.cmds = ft_split(str, ' ');
		//printf("cmd[%i] = %s\n", i, cmd.cmds[i]);
		i++;
	}
	if (ft_check_cmds(&arg) == 1)
	{
		//ft_exit
		return ;
	}
	i = 0;
	while (arg.cmds[i])
		i++;
	arg.count = i;
	i = 0;
	while (i < arg.count)
	{
		i = ft_get_cmd(&arg);
		//printf("i = %d\n", i);
		if (i == -1)
		{
			return ; // sortir
		}
		i++;
	}
}
*/

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
	/*while (cmd->cmds[i])
	{
		j = 0;
		while (cmd->cmds[i][j])
		{
			if (cmd->cmds[i][j] == '\\' || cmd->cmds[i][j] == ';')
				// erreur ou le passer sans rien faire???
				return (1); // si considere comme erreur ou (0) si skip
			j++;
		}
		i++;
	}*/
	if (ft_check_quotes(arg) == 1)
	{	// erreur ou le passer sans rien faire???
		return (1); // si considere comme erreur ou (0) si skip
	}
	return (0);
}

int	ft_check_quotes(t_arg *arg)
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