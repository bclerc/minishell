/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envgeter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:40:57 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/03 11:03:12 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		i++;
	while (i >= 0)
	{
		free(split[i]);
		i--;
	}
	free(split);
}

int	get_count(char **str)
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
	final_str = (char *)malloc(count + 4);
	i = 0;
	count = 0;
	ft_bzero(final_str, count + 4);
	while (str[i])
	{
		y = 0;
		while (str[i][y])
		{
			final_str[count] = str[i][y];
			count++;
			y++;
		}
		final_str[count] = ' ';
		count++;
		i++;
	}
	printf("Writed :  %d Alloced : %d\n", count + 1, count + 1);
	exit(1);
	return (final_str);
}

char	*transform_str(char *str)
{
	int		i;
	char	**split;
	char	*env;
	char	*ret;

	split = ft_strsplit(str, ' ');

	i = 0;
	while (split[i])
	{
		if (split[i][0] == '$')
		{
			env = get_env_variable(split[i] + 1);
			printf("Env is %s\n", env);
			if (env)
			{
				free(split[i]);
				split[i] = ft_strdup(env);
			}
		}
		i++;
	}
	ret = build_str(split);
	rm_split(split);
	free(str);
	return (ret);
}
