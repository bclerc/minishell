/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 10:02:07 by asgaulti          #+#    #+#             */
/*   Updated: 2022/01/11 15:36:58 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_arg(t_arg *arg, char *str)
{
	ft_bzero(arg, sizeof(t_arg));
	if (str)
		arg->count = 1;
}

t_data	*ft_init_data(t_data *data)
{
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->fd_in = NULL;
	data->msg = NULL;
	data->std_in = 0;
	return (data);
}

int	ft_init_cmd(t_cmd **cmd, t_arg *arg)
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
