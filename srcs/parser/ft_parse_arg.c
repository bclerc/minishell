/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:38:12 by astrid            #+#    #+#             */
/*   Updated: 2021/10/16 15:05:17 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_parse_pipe(char *str, int i, int start)
{
	char	*tmp;
	int 	c;

	tmp = malloc(sizeof(char) * i);
	while (start < i)
	{
		tmp[c] = str[start];
		start++;
		c++;
	}
	return (tmp);
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
		arg->cmds[c] = "<<";
}

/*
char    *ft_parse_chevron(char *str, int i, int start)
{
    char    *tmp;
    
    if (str[i] == '>' && str[i + 1] == '>')
    {
        
    }
    else if (str[i] == '>' && str[i + 1] != '>')
    {
        
    }
}
*/
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
	return (tmp);
}
