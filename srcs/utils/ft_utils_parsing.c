/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:41:17 by user42            #+#    #+#             */
/*   Updated: 2022/01/12 18:11:50 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_sep(t_arg *arg, int i, char c, int count)
{
	int	z;

	z = 0;
	while (z < count)
	{
		arg->cmds[i] = &c;
		z++;
	}
	return (arg->cmds[i]);
}

char	*ft_check_quotes(char *str, t_arg *arg, char *tmp, int size)
{
	if (str[arg->pos_i] == '\'')
	{
		str = ft_sq(arg, str, tmp);
		if (!str)
			return (NULL);
		arg->pos_i -= 2;
		size -= 2;
	}
	else if (str[arg->pos_i] == '"')
	{
		str = ft_dq(arg, str, tmp);
		if (!str)
			return (NULL);
		if (ft_strncmp(arg->cmds[arg->i_cpy], "export", 6) == 0)
		{
			arg->pos_i += 2;
			size -= 1;
		}
		else
		{
			arg->pos_i -= 2;
			size -= 2;
		}
	}
	return (str);
}

char	*ft_cut_quote_export(char *str, int start, int end)
{
	char	*dest;
	int		size;
	int		i;

	size = ft_strlen(str) - start;
	i = 0;
	dest = malloc(sizeof(char) * (size + 2));
	if (!dest)
		return (NULL);
	while (start <= end)
		dest[i++] = str[start++];
	dest[i] = '^';
	i++;
	if (i < size -1)
	{
		while (i < size)
		{
			dest[i] = str[start + 1];
			start++;
			i++;
		}
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_i_quotes(int i, t_arg *arg, char *str)
{
	i = arg->pos_i;
	i++;
	while (str[i] != '"')
	{
		if (str[i] == '"')
			arg->count_quote++;
		i++;
	}
	if (arg->count_quote % 2 != 0)
		return (ft_print("There is an error with quotes", -1), 0);
	arg->pos_i = i;
	return (i);
}

int	ft_i_quote(int i, t_arg *arg, char *str)
{
	i = arg->pos_i;
	i++;
	while (str[i] != '\'')
	{
		if (str[i] == '\'')
			arg->count_quote++;
		i++;
	}
	if (arg->count_quote % 2 != 0)
		return (ft_print("There is an error with quotes", -1), 0);
	arg->pos_i = i;
	return (i);
}
