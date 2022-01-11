/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inout.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:56:36 by asgaulti          #+#    #+#             */
/*   Updated: 2022/01/11 14:27:36 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_inout(t_cmd *tmp, t_cmd *cmd, t_redir *redir)
{
	t_cmd	*cpy;
	t_data	*data;

	ft_bzero(data, sizeof(t_data));
	while (tmp && tmp->prev != NULL)
	{
		while (tmp->prev && (tmp->prev->std >= 2 && tmp->prev->std <= 5))
			data = ft_check_in(tmp, data);
	}
	printf("data fd %s std %d msg %s\n", data->fd_in, data->std_in, data->msg);
	return (NULL);
}

t_data	*ft_check_in(t_cmd *tmp, t_data *data)
{
	
}
