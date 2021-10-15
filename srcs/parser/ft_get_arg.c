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
	int		i;

	i = 0;
	while (i < arg->count)
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			arg->cmds[i] = ft_strtrim(str, '<');
			printf("cmd1[%d] = %s\n", i, arg->cmds[i]);
			i++;
			arg->cmds[i] = ft_sep(arg, i, '<', 2);
			printf("cmd2[%d] = %s\n", i, arg->cmds[i]);
			i++;
		}
		else if (str[i] == '>' && str[i + 1] == '>')
		{
			arg->cmds[i] = ft_strtrim(str, '>');
			printf("cmd3[%d] = %s\n", i, arg->cmds[i]);
			i++;
			arg->cmds[i] = ft_sep(arg, i, '>',2);
			printf("cmd4[%d] = %s\n", i, arg->cmds[i]);
			i++;
		}
		else if (str[i] == '>')
		{
			arg->cmds[i] = ft_strtrim(str, '>');
			printf("cmd5[%d] = %s\n", i, arg->cmds[i]);
			arg->cmds[i] = ft_sep(arg, i, '>', 1);
			printf("cmd6[%d] = %s\n", i, arg->cmds[i]);
			i++;
		}	
		else if (str[i] == '<')
		{
			arg->cmds[i] = ft_strtrim(str, '<');
			printf("cmd7[%d] = %s\n", i, arg->cmds[i]);
			arg->cmds[i] = ft_sep(arg, i, '<', 1);
			printf("cmd8[%d] = %s\n", i, arg->cmds[i]);
			i++;
		}
		else if (str[i] == '|')		
		{
			arg->cmds[i] = ft_strtrim(str, '|');
			printf("cmd9[%d] = %s\n", i, arg->cmds[i]);
			arg->cmds[i] = ft_sep(arg, i, '|', 1);
			printf("cmd10[%d] = %s\n", i, arg->cmds[i]);
			i++;
		}
		i++;
	}
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