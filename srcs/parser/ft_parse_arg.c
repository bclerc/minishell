/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:38:12 by astrid            #+#    #+#             */
/*   Updated: 2021/12/01 15:06:51 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*ft_parse_arg(char *str, int i, t_arg *arg)
{
	char	*tmp;
	int		c;

	c = 0;
	tmp = malloc(sizeof(char) * (i + 1));
	while (arg->start < i)
	{
		tmp[c] = str[arg->start];
		arg->start++;
		c++;
	}
	tmp[c] = '\0';
	return (tmp);
}

int	ft_check_char(char *str, int i, int c, t_arg *arg)
{
	if (str[i] == '|')
	{
		if (str[i + 1] == '|')
			return (ft_print("There are two many pipes\n", -1) & -1); //gerer la sortie (actuellement continue a parser)
		ft_char(arg, c, '|', 1);
	}
	else if (str[i] == '<' || str[i] == '>')
	{
		if (str[i] == '>' && str[i + 1] == '>')
		{
			ft_char(arg, c, '>', 2);
			i++;
		}
		else if (str[i] == '<' && str[i + 1] == '<')
		{
			ft_char(arg, c, '<', 2);
			i++;
		}
		else if (str[i] == '<'&& str[i + 1] != '<')
			ft_char(arg, c, '<', 1);
		else if (str[i] == '>'&& str[i + 1] != '>')
			ft_char(arg, c, '>', 1);
	}
	i++;
	return (i);
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
	else if (s == '>' && nb == 2)
		arg->cmds[c] = ">>";
	else if (s == '>' && nb == 1)
		arg->cmds[c] = ">";
	else if (s == '<' && nb == 2)
		arg->cmds[c] = "<<";
	else if (s == '<' && nb == 1)
		arg->cmds[c] = "<";
}

char	*ft_nosep(int i, char *str, t_arg *arg)
{
	int z;
	char	*tmp;

	z = 0;
	tmp = malloc(sizeof(char) * (i - arg->start) + 1);
	if (!tmp)
		return (NULL);
	if (arg->count != 1)
		arg->start++;
	while (arg->start < i)
	{
		tmp[z] = str[arg->start];
		z++;
		arg->start++;
	}
	tmp[z] = '\0';
	//printf("tmp = %s\n", tmp);
	return (tmp);
}
