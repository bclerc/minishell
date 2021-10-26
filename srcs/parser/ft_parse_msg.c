/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 10:04:00 by astrid            #+#    #+#             */
/*   Updated: 2021/10/26 10:54:22 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_search_msg(char **cpy, int i, int j, t_arg *arg, char *tmp)
{
	int		start;
	
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
	return (tmp);
}

char	*ft_parse_msg(char *cpy, char *tmp, t_arg *arg)
{
	int i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = ft_strlen(cpy);
	tmp = malloc(sizeof(char) * (size + 1));
	if (!tmp)
		return (NULL);
	while (cpy[i])
	{
		if (cpy[i] == '\"')
			i = ft_doubleq(cpy, i);
		if (cpy[i] == '\'')
			i = ft_simpleq(cpy, i);
		if (cpy[i] != '\"' || cpy[i] != '\'')
			tmp[j] = cpy[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	printf("tmp = %s\n", tmp);
	return (tmp);
}

int	ft_doubleq(char *cpy, int i)
{
	if (cpy[i + 1] == '\"')
		i++;
	i++;
	return (i);
}

int	ft_simpleq(char *cpy, int i)
{
	if (cpy[i + 1] == '\'')
		i++;
	i++;
	return (i);
}

/*
char	*ft_msg_quotes(char *cpy, char *tmp, int i)
{
	int	j;

	j = 0;
	if (cpy[i] == '\"')
	{
		if (cpy[i + 1] == '\"')
			tmp = '\n';
	}
	arg->quote = i;
	return (tmp);
}
*/
int	ft_pos(char *cpy, int i)
{
	if (cpy[i] == '\"')
	{
		while (cpy[i] != '\"')
			i++;
	}
	else if (cpy[i] == '\'')
	{
		while (cpy[i] != '\'')
			i++;
	}
	return (i);
}
