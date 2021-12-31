/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:05:34 by astrid            #+#    #+#             */
/*   Updated: 2021/12/30 15:04:46 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_get_cmd(t_arg *arg, t_cmd **cmd)
{
	int		i;
	char	**cpy;
	t_cmd	*tmp;

	i = 0;
	tmp = *cmd;
	while (i < arg->count)
	{
		if ((ft_check_redir(arg, i) == 1 && (i + 1 < arg->count))
			|| (ft_check_redir(arg, i) == 2 && (i + 1 < arg->count)))
			i ++;
		cpy = ft_strsplit(arg->cmds[i], ' ');
		if (!cpy[0])
			m_exit(*cmd, M_EXIT_MALLOC_ERROR, "t_cmd	*ft_get_cmd(t_arg *arg, t_cmd **cmd)");
		if (cpy[0][0] == '\'' || cpy[0][0] == '"')
		{
			cpy[0] = ft_strsub(cpy[0], 1, ft_strlen(cpy[0]) - 2);
			//cpy[0] = ft_cmd_quotes(cpy[0]);
			if (!cpy[0])
				return (NULL);
			arg->q = 1;
		}
		printf("cpy[] %s\n", cpy[0]);
		if (cpy[i] == NULL && i < arg->count)
		{
			cpy[i] = ft_strdup(arg->cmds[i]);
			if (!cpy[i])
				return (NULL);
		}
		arg->i_cpy = i++;
		*cmd = ft_parse_cmd(arg, cpy, *cmd);
		if (!*cmd)
			return (NULL);
		
	}
	return (*cmd);
}

t_cmd	*ft_parse_cmd(t_arg *arg, char **cpy, t_cmd *cmd)
{
	if (ft_strcmp(cpy[0], "echo") == 0)
	{
		return (ft_parse_echo(arg, cpy, cmd));
	}
	else if (ft_strcmp(cpy[0], "cd") == 0 || ft_strcmp(cpy[0], "pwd") == 0
		|| ft_strcmp(cpy[0], "export") == 0
		|| ft_strcmp(cpy[0], "unset") == 0
		|| ft_strcmp(cpy[0], "env") == 0 || ft_strcmp(cpy[0], "exit") == 0)
		return (ft_parse_builtins(arg, cpy, cmd));
	else if (ft_strcmp(cpy[0], "|") && ft_strcmp(cpy[0], ">")
		&& ft_strcmp(cpy[0], ">>") && ft_strcmp(cpy[0], "<")
		&& ft_strcmp(cpy[0], "<<"))
		return (ft_parse_other(arg, cpy, cmd));
	return (NULL);
}

int	ft_check_redir(t_arg *arg, int i)
{
	if (ft_strcmp(arg->cmds[i], "|") == 0
		|| ft_strcmp(arg->cmds[i], ">") == 0
		|| ft_strcmp(arg->cmds[i], "<") == 0)
		return (1);
	else if (ft_strcmp(arg->cmds[i], ">>") == 0
		|| ft_strcmp(arg->cmds[i], "<<") == 0)
		return (2);
	return (0);
}

char	*ft_cmd_quotes(char *cpy)
{
	int		i;
	int		j;
	int		size;
	char	*tmp;

	i = 0;
	j = 1;
	size = ft_strlen(cpy) - 2;
	tmp = malloc(sizeof(char) * (size + 1));
	if (!tmp)
		return (NULL);
	while (i < size)
	{
		tmp[i] = cpy[j];
		i++;
		j++;
	}
	tmp[i] = '\0';
	return (tmp);
}