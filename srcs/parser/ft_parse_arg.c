/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:38:12 by astrid            #+#    #+#             */
/*   Updated: 2021/10/16 16:19:44 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_char(char *str, int i, int c, t_arg *arg)
{
	if (str[i] == '|')
		ft_char(arg, c, '|', 1);
	else if (str[i] == '<' || str[i] == '>')
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			ft_char(arg, c, '<', 2);
			i++;
			return ;
		}
		else if (str[i] == '>'&& str[i + 1] == '>')
		{
			ft_char(arg, c, '>', 2);
			i++;
			return ;
		}
		else if (str[i] == '<'&& str[i + 1] != '<')
			ft_char(arg, c, '<', 1);
		else if (str[i] == '>'&& str[i + 1] != '>')
			ft_char(arg, c, '>', 1);
	}
}

void	ft_char(t_arg *arg, int c, char s, int nb)
{
	if (nb == 1)
		arg->cmds[c] = malloc(sizeof(char));
	else if (nb == 2)
		arg->cmds[c] = malloc(sizeof(char) * 2);
	if (!arg->cmds[c])
		return ;
	if (s == '|')
		arg->cmds[c] = "|";
	else if (s = '>' && nb == 2)
		arg->cmds[c] = ">>";
	else if (s = '>' && nb == 1)
		arg->cmds[c] = ">";
	else if (s = '<' && nb == 2)
		arg->cmds[c] = "<<";
	else if (s = '<' && nb == 1)
		arg->cmds[c] = "<";
}

char	*ft_parse_cmds(char *str, int i, int start)
{
	char	*tmp;
	int		c;

	c = 0;
	tmp = malloc(sizeof(char) * (i + 1));
	while (start < i)
	{
		tmp[c] = str[start];
		start++;
		c++;
	}
	tmp[c] = '\0';
	return (tmp);
}

char	*ft_nosep(int i, int start, char *str, t_arg *arg)
{
	int z;
	char	*tmp;

	z = 0;
	tmp = malloc(sizeof(char) * (i - start));
	if (!tmp)
		return (NULL);
	if (arg->count != 1)
		start++;
	while (start < i)
	{
		tmp[z] = str[start];
		z++;
		start++;
	}
	tmp[z] = '\0';
	printf("tmp = %s\n", tmp);
	return (tmp);
}
