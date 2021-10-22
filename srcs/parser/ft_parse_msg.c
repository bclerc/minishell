/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 10:04:00 by astrid            #+#    #+#             */
/*   Updated: 2021/10/22 12:04:00 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_parse_msg(t_arg *arg, char **cpy, int i)
{
	int j;

	while (i < arg->cpy_nb)
	{
		j = 0;
		while (cpy[i][j])
		{
			if (cpy[i][j] == "\"" || cpy[i][j] == '\'')
				ft_msg_quotes(cpy, i, j);
			// else if (cpy[i][j] == '$' && (cpy[i][j - 1] != "\"" || cpy[i][j - 1] != "\'"))
			//		ft_msg_dollar(cpy, i, j);
			j++;
		}
		i++;
	}
	return (cpy[i]);
}

char	*ft_msg_quotes(char **cpy, int i, int j)
{
	
}