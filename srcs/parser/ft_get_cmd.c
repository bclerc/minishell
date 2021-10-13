#include "minishell.h"

void	ft_get_cmd(char *str)
{
	int		i;
	t_cmd	cmd;

	i = 0;
	ft_init_cmd(&cmd);
	//cmd.arg = str;
	while (str[i])
	{
		cmd.cmds = ft_split(str, ' ');
		//printf("cmd[%i] = %s\n", i, cmd.cmds[i]);
		i++;
	}
	if (ft_check_cmds(&cmd) == 1)
	{
		//ft_exit
		return ;
	}
}

void	ft_init_cmd(t_cmd *cmd)
{
	ft_bzero(cmd, sizeof(t_cmd));
}

int	ft_check_cmds(t_cmd *cmd)
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
	if (ft_check_quotes(cmd) == 1)
	{	// erreur ou le passer sans rien faire???
		return (1); // si considere comme erreur ou (0) si skip
	}
	return (0);
}

int	ft_check_quotes(t_cmd *cmd)
{
	int	i;
	int	j;
	
	i = 0;
	while (cmd->cmds[i])
	{
		j = 0;
		while (cmd->cmds[i][j])
		{
			if (cmd->cmds[i][j] == '\'')
				cmd->count_quote++;
			else if (cmd->cmds[i][j] == '"')
				cmd->count_quotes++;
			j++;
		}
		if (cmd->count_quote % 2 != 0 || cmd->count_quote % 2 != 0)
			return (ft_print("Error : There is an odd number of quotes\n", 1));
		i++;
	}
	return (0);
}