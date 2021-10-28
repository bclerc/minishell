/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 12:10:09 by astrid            #+#    #+#             */
/*   Updated: 2021/10/28 12:27:40 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_cpy_msg(t_arg *arg, char **cpy, int i, int j, t_cmd *new)
{
	char	*tmp;
	char	*tmp2;
	int		c;

//printf("j = %d nb = %d\n", j, new->cpy_nb - 1);
	if (j == new->cpy_nb - 1)
	{
		tmp = ft_parse_msg(cpy[j], tmp, arg);	
		//cmd->msg = ft_strdup(tmp);
		//free(tmp);
		return (tmp);
	}
	else
	{
		tmp = ft_search_msg(cpy, i, j, arg, tmp);
		tmp2 = ft_parse_msg(tmp, tmp2, arg);
		//cmd->msg = ft_strdup(tmp2);
		//free(tmp);
		//free(tmp2);
		return (tmp2);
	}
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
	return (7);
}

char	*ft_msg(t_arg *arg, int i, int start, char *tmp)
{
	int	size;
	int	a;
	
	size = ft_strlen(arg->cmds[i]);
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