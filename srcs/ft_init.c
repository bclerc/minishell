/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 10:02:07 by asgaulti          #+#    #+#             */
/*   Updated: 2021/12/21 15:07:10 by asgaulti         ###   ########.fr       */
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
	(void)arg;
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
