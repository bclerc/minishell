/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:19:56 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/12 18:38:50 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_in_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*fill(const char *str, char *set, int *i)
{
	int		k;
	char	*s;

	s = (char *)malloc(sizeof(s) * (ft_strlen(str)));
	if (!(s))
		return (NULL);
	k = 0;
	while ((!is_in_set(str[*i], set)) && str[*i])
	{
		s[k] = str[*i];
		k++;
		*i += 1;
	}	
	s[k] = '\0';
	return (s);
}

void	replace_var(char save, char **s, int status)
{
	char	*tmp;
	char	*stat;

	if (save == '$')
	{
		tmp = *s;
		if (tmp[0] == '?')
		{
			stat = ft_itoa(status);
			*s = ft_strjoin(stat, *s + 1);
			free(tmp);
			free(stat);
		}
		tmp = *s;
		if (ft_strlen(*s) > 0)
			*s = ft_strdup(get_env_variable(tmp));
		else
			*s = ft_strdup("	");
		free(tmp);
	}
}
