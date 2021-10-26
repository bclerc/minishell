/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 10:04:00 by astrid            #+#    #+#             */
/*   Updated: 2021/10/26 09:52:29 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (cpy[i] == '\"' || cpy[i] == '\'')
			i++;
		if (cpy[i] != '\"' || cpy[i] != '\'')
			tmp[j] = cpy[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	printf("tmp = %s\n", tmp);
	return (tmp);
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
