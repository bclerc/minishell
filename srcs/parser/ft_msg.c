/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 12:10:09 by astrid            #+#    #+#             */
/*   Updated: 2021/12/31 11:22:53 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_cpy_msg(t_arg *arg, char **cpy, int j, t_cmd *new)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	if (j == new->cpy_nb - 1)
	{
		tmp = ft_parse_msg(cpy[j], arg);
		if (!tmp)
			return (NULL);
		return (tmp);
	}
	else
	{
		tmp = ft_search_msg(cpy, j, arg, tmp);
		tmp2 = ft_parse_msg(tmp, arg);
		if (!tmp)
			return (NULL);
		return (tmp2);
	}
}

int	ft_which_cmd(char **cpy)
{
	if (ft_strncmp(cpy[0], "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(cpy[0], "cd", 2) == 0)
		return (2);
	else if (ft_strncmp(cpy[0], "pwd", 3) == 0
		|| ft_strncmp(cpy[0], "env", 3) == 0)
		return (3);
	else if (ft_strncmp(cpy[0], "exit", 4) == 0)
		return (4);
	else if (ft_strncmp(cpy[0], "unset", 5) == 0)
		return (5);
	else if (ft_strncmp(cpy[0], "export", 6) == 0)
		return (6);
	return (7);
}

char	*ft_msg(t_arg *arg, int start, char *tmp)
{
	int	size;
	int	a;

	size = ft_strlen(arg->cmds[arg->i_cpy]);
	tmp = malloc(sizeof(char) * (size - start + 1));
	if (!tmp)
		return (NULL);
	a = 0;
	while (start < size)
	{
		tmp[a] = arg->cmds[arg->i_cpy][start];
		a++;
		start++;
	}
	tmp[a] = '\0';
	return (tmp);
}

char	*ft_other_msg(t_arg *arg, int start, char *tmp)
{
	int	size;
	int	a;

	size = ft_strlen(arg->cmds[arg->i_cpy]);
	tmp = malloc(sizeof(char) * (size - start + 1));
	if (!tmp)
		return (NULL);
	a = 0;
	while (start < size)
	{
		tmp[a] = arg->cmds[arg->i_cpy][start];
		a++;
		start++;
	}
	tmp[a] = '\0';
	return (tmp);
}

char	*ft_which_nb(int start, char *tmp, t_arg *arg)
{
	if (start == 1)
	{
		if (!arg->spec_n && arg->q == 0)
			start = 5;
		else if (!arg->spec_n && arg->q == 1)
			start = 7;
		else if (ft_strcmp(arg->spec_n, "-n") == 0 && arg->q == 0)
			start = 6 + arg->n + 1;
		else if (ft_strcmp(arg->spec_n, "-n") == 0 && arg->q == 1)
			start = 8 + arg->n + 1;
		tmp = ft_msg(arg, start, tmp);
	}
	else
		tmp = ft_msg(arg, start + 1, tmp);
	return (tmp);
}
