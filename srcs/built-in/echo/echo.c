/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:23:17 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/14 17:15:02 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	echo(char *str, char *path, int flag_n)
{
	(void)flag_n;
	if (str)
		write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (1);
}
