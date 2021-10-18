/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envgeter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:40:57 by bclerc            #+#    #+#             */
/*   Updated: 2021/10/18 11:02:41 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	while (i > 0)
	{
		free(split[i]);
		i--;
	}
	free(split);
}

int		get_count(char **str)
{
	int	i;
	int	y;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		y = 0;
		while (str[i][y])
		{
			count++;
			y++;
		}
		i++;
	}
	return (count);
}
char	*build_str(char **str)
{
	char	*final_str;
	int		count;
	int		i;
	int		y;

	count = get_count(str);
	final_str = (char*)malloc(sizeof(char) * count + 1);
	i = 0;
	count = 0;
	while (str[i])
	{
		y = 0;
		while (str[i][y])
		{
			final_str[count] = str[i][y];
			count++;
			y++;
		}
		i++;
	}
	final_str[count] = 0;
	return (final_str);
}

char	*transform_str(char *str, char **envp)
{
	int		i;
	char	**split;
	char	*env;
	char	*ret;

	split = ft_strsplit_s(str, '$');
	i = 0;
	while (split[i])
	{
		if (split[i][0] == '$')
		{
			env = get_env_variable(split[i] + 1, envp);
			if (env)
				split[i] = env;
		}
		i++;
	}
	ret = build_str(split);
	rm_split(split);
	return (ret);
}
