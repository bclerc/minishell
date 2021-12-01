/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:13:26 by bclerc            #+#    #+#             */
/*   Updated: 2021/12/01 13:53:48 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../include/minishell.h"

int is_unset_var(char **var, char *value)
{
	int i;

	i = 0;
	while (var[i])
	{
		if (!var[i])
			return (0);
		if (ft_strncmp(var[i], value, ft_strlen(var[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	unset(char *var)
{
	char	**tmp;
	char	**vars;
	int		length;
	int		i;
	int		b;

	if (!var)
		return (-1);
	vars = ft_strsplit(var, ' ');
	if (!vars)
		return (-1);
	length = get_env_length(core->envp);
	b = get_env_length(vars);
	tmp = (char **)malloc(sizeof(char *) * (length - b));
	i = 0;
	b = 0;
	while (i < length)
	{
		if (!is_unset_var(vars, core->envp[i]))
		{
			tmp[b] = ft_strdup(core->envp[i]);
			b++;
		}
		i++;
	}
	tmp[b] = 0;
	change_env(tmp);
	i = 0;
	while (core->envp[i]);
	printf("Readed = %d\n", i - 1);
	return (1);
}