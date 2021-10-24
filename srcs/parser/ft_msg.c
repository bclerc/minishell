/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 12:10:09 by astrid            #+#    #+#             */
/*   Updated: 2021/10/24 16:19:25 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cpy_msg(t_arg *arg, char **cpy, int i, int j, t_cmd *cmd)
{
	char	*tmp;
	int		c;
	int		start;
    
	//printf("cpy[%d] = %s\n", i, cpy[i]);
	// if (!cpy[i])
	// 	return (ft_print("\n", -1));
	//cpy[i] = ft_parse_msg(cmd, cpy, i);
	if (j == cmd->cpy_nb - 1)
		cmd->msg = ft_strdup(cpy[j]);
	else
	{
		start = ft_which_cmd(cpy);
		if (start == 7)
		{
			start = ft_strlen(cpy[0]);
			tmp = ft_other_msg(arg, i, start, tmp);
		}	
		if (j == 1)
			tmp = ft_which_nb(start, tmp, arg, i);
		else if (j == 2)
		{
			start = 8;
			tmp = ft_msg(arg, i, start, tmp);
		}
		cmd->msg = ft_strdup(tmp);
		free(tmp);
	}
	printf("cmd->msg = %s\n", cmd->msg);
}

int	ft_which_cmd(char **cpy)
{
	if (ft_strncmp(cpy[0], "echo", ft_strlen(cpy[0])) == 0)
		return (1);
	else if (ft_strncmp(cpy[0], "cd", ft_strlen(cpy[0])) == 0)
		return (2);
	else if (ft_strncmp(cpy[0], "pwd", ft_strlen(cpy[0])) == 0
			|| ft_strncmp(cpy[0], "env", ft_strlen(cpy[0])) == 0)
		return (3);
	else if (ft_strncmp(cpy[0], "exit", ft_strlen(cpy[0])) == 0)
		return (4);
	else if (ft_strncmp(cpy[0], "unset", ft_strlen(cpy[0])) == 0)
		return (5);
	else if (ft_strncmp(cpy[0], "export", ft_strlen(cpy[0])) == 0)
		return (6);
	else
		return (7);
}

char	*ft_msg(t_arg *arg, int i, int start, char *tmp)
{
	int	size;
	int	a;
	
	size = ft_strlen(arg->cmds[i]);
	printf("size = %d start = %d i = %d cmds = %c\n", size, start, i, arg->cmds[i][start]);
	tmp = malloc(sizeof(char) * (size - start + 1));
	if (!tmp)
		return (NULL);
	a = 0;
	while (start < size)
	{
		tmp[a] = arg->cmds[i][start];
		a++;
		start++;
	}
	tmp[a] = '\0';
	return (tmp);
}

char	*ft_other_msg(t_arg *arg, int i, int start, char *tmp)
{
	int	size;
	int	a;
	
	size = ft_strlen(arg->cmds[i]);
	printf("size = %d start = %d i = %d cmds = %c\n", size, start, i, arg->cmds[i][start]);
	tmp = malloc(sizeof(char) * (size - start + 1));
	if (!tmp)
		return (NULL);
	a = 0;
	while (start < size)
	{
		tmp[a] = arg->cmds[i][start];
		a++;
		start++;
	}
	tmp[a] = '\0';
	return (tmp);
}

char	*ft_which_nb(int start, char *tmp, t_arg *arg, int i)
{
	if (start == 1)
	{
		start = 5;
		tmp = ft_msg(arg, i, start, tmp);
	}
	else
		tmp = ft_msg(arg, i, start + 1, tmp);
	return (tmp);
}