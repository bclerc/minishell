#include "minishell.h"
/*
void	ft_get_arg(char *str)
{
	int		i;
	t_arg arg;

	i = 0;
	ft_init_arg(&arg);
	while (str[i])
	{
		if ((str[i] == '>' && str[i + 1] == '>') || 
			(str[i] == '<' && str[i + 1] == '<')) ||
			str[i] == '>' || str[i] == '<' || str[i] == '|')
			arg.count++;
		i++;
	}
	printf("c = %d\n", arg.count);
	if (!arg.count)
	{
		ft_print("There is no command, try again!\n", -1);
		return ;
	}
}
*/

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


void	ft_init_arg(t_arg *arg)
{
	ft_bzero(arg, sizeof(t_arg));
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