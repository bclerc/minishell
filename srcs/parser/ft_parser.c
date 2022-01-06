/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:29:13 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/03 14:24:02 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// launch parsing
// init struct arg & cmd
t_cmd	*ft_launch_parser(char *str, t_cmd **cmd)
{
	int		i;
	t_arg	arg;
	t_cmd	*tmp;

	i = 0;
	tmp = *cmd;
	if (ft_get_arg(str, &arg) == -1)
		return (NULL);
	if (ft_init_cmd(cmd, &arg) < 0)
		return (NULL);
	*cmd = ft_get_cmd(&arg, cmd);
	if (!*cmd)
		return (NULL);
	return (*cmd);
}

int	ft_no(char *str)
{
	int	i;

	i = 0;
	while (str && str[i + 1] != '\0')
		i++;
	if (str[i - 1] == '|' || str[i - 1] == '>' || str[i - 1] == '<')
		return (-1);
	return (0);
}
