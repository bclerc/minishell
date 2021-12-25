/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 10:02:07 by asgaulti          #+#    #+#             */
/*   Updated: 2021/12/25 18:54:23 by astrid           ###   ########.fr       */
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

int	ft_init_redir(t_redir *redir)
{
	ft_bzero(redir, sizeof(t_redir));
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
