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
		exit (1);
	}
}

void	ft_init_cmd(t_cmd *cmd)
{
	ft_bzero(cmd, sizeof(t_cmd));
}

int	ft_check_cmds(t_cmd *cmd)
{
	int	i;
	
	//ft_check_quotes(&cmd);
	i = 0;
	while (cmd->cmds[i])
	{
		j = 0;
		while (cmd->cmds[i][j])
		{
			if (cmd->cmds[i][j] == '\\' || cmd->cmds[i][j] == ';')
				// erreur ou le passer sans rien faire???
		}
	}
}