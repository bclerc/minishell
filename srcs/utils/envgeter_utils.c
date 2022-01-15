/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envgeter_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:50:56 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/14 15:53:17 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_value(t_split *src, t_split *dst)
{
	t_split	*tmp;

	tmp = dst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = src;
}

char	*to_string(t_split *split)
{
	t_split	*tmp;
	int		len;
	char	*ret;

	len = 0;
	tmp = split;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	ret = (char *)malloc(sizeof(char) * len + 1);
	if (!ret)
		return (NULL);
	len = 0;
	while (split)
	{
		ret[len] = split->value;
		len++;
		tmp = split->next;
		free(split);
		split = tmp;
	}
	ret[len] = 0;
	return (ret);
}

t_split	*get_str(char *str, int len)
{
	t_split	*split;
	t_split	*new;
	int		i;

	i = 0;
	split = NULL;
	while (i < len)
	{
		new = (t_split *)malloc(sizeof(t_split));
		new->value = str[i];
		new->next = NULL;
		if (split != NULL)
			add_value(new, split);
		else
			split = new;
		i++;
	}
	return (split);
}

t_split	*change_value(t_split *start, t_split *end, int status)
{
	t_split	*tmp_spl;
	t_split	*test;
	char	*tmp;
	char	*env;

	tmp = to_string(start);
	if (ft_strcmp(tmp, "?") == 0)
		env = ft_itoa(status);
	else
		env = get_env_variable(tmp);
	tmp_spl = get_str(env, ft_strlen(env));
	if (ft_strcmp(tmp, "?") == 0)
		free(env);
	free(tmp);
	test = tmp_spl;
	while (test->next)
		test = test->next;
	test->next = end;
	return (tmp_spl);
}
