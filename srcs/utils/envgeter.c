/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envgeter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:40:57 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/04 15:21:10 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i] != NULL)
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
		count++;
		i++;
}
	return (count);
}

char	*build_str(char **str)
{
	char	*final_str;
	int		i;
	int		count;
	int		y;

	final_str = NULL;
	count = get_count(str);
	final_str = (char *)malloc(sizeof(char) * (count + 2));
	if (!final_str)
		return (NULL);
	i = 0;
	count = 0;
	ft_bzero(final_str, count + 1);
	while (str[i])
	{
		y = 0;
		while (str[i][y])
		{
			final_str[count] = str[i][y];
			count++;
			y++;
		}
		if (str[i + 1] != NULL)
		{
			final_str[count] = ' ';
			count++;
		}
		i++;
	}
	final_str[count] = '\0';
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
