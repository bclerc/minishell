/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 10:02:07 by asgaulti          #+#    #+#             */
/*   Updated: 2021/11/04 16:45:54 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_arg(t_arg *arg, char *str)
{
	ft_bzero(arg, sizeof(t_arg));
	if (str)
		arg->count = 1;
}

int ft_init_cmd(t_cmd **cmd, t_arg *arg)
{
	ft_bzero(cmd, sizeof(t_cmd));
	return (0);
}

// t_token	*ft_init_token(t_token *token)
// {
// 	token = malloc(sizeof(t_token));
// 	if (token == NULL)
// 		return (NULL);
// 	*token = (t_token){-1, -1, -1, -1};
// 	return (token);
// }
