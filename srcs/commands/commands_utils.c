/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 17:03:27 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/28 17:06:55 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**no_argv(t_cmd *cmd)
{
	char	**ret;

	ret = (char **)malloc(sizeof(char *) * 2);
	if (!ret)
		m_exit(cmd, M_EXIT_MALLOC_ERROR, "char **no_argv(t_cmd *cmd)");
	ret[0] = cmd->cmd;
	ret[1] = NULL;
	return (ret);
}

char	**get_argv(t_cmd *cmd)
{
	char	**ret;
	char	**tmp;
	int		i;

	if (!cmd->msg)
		return (no_argv(cmd));
	tmp = ft_strsplit(cmd->msg, ' ');
	if (!tmp)
		return (NULL);
	i = 0;
	while (tmp[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * (i + 2));
	if (!ret)
		m_exit(cmd, M_EXIT_MALLOC_ERROR, "char **get_argv(t_cmd *cmd)");
	ret[0] = cmd->cmd;
	i = 0;
	while (tmp[i])
	{
		ret[i + 1] = ft_strdup(tmp[i]);
		i++;
	}
	ret[i + 1] = NULL;
	rm_split(tmp);
	return (ret);
}
