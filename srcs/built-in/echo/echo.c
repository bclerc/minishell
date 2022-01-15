/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:23:17 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/13 12:47:07 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	echo(t_cmd *cmd)
{
	char	*str;

	str = cmd->msg;
	if (str)
		write(1, str, ft_strlen(str));
	if (!cmd->spec)
		write(1, "\n", 1);
	exit(EXIT_SUCCESS);
}
