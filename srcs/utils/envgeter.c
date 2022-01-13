/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envgeter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:40:57 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/13 17:15:32 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	add_value(t_split *src, t_split *dst)
{
	t_split *tmp;

	tmp = dst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = src;	
}

char	*to_string(t_split *split)
{
	t_split *tmp;
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
	t_split *new;
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

t_split *change_value(t_split *start, t_split *end, int status)
{
	t_split *tmp_spl;
	t_split *test;
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
	test = tmp_spl;
	while (test->next)
		test = test->next;
	test->next = end;
	return (tmp_spl);
}

t_split *change_str(t_split *split, int status)
{
	t_split *tmp;
	t_split	*start;
	t_split *end;
	t_split	*next;
	t_split	*last;

	start = NULL;
	end	= NULL;
	tmp = split;
	last = tmp;

	while (tmp)
	{
		if (tmp->value == '$' && tmp->next && tmp->next->value != ' ' && last->value != '\'')
		{
			start = tmp->next;
			if (start->value != '?')
			{
				while (start->next && start->next->value != ' ' && start->next->value != '$' && start->next->value != '"')
				start = start->next;
			}
			next = start->next;
			start->next = NULL;
			end = start;
			start = tmp->next;
			free(tmp);
			tmp = change_value(start, next, status);
			if (split == last)
				split = tmp;
			else
				last->next = tmp;
		}	
		last = tmp;
		tmp = tmp->next;
	}
	return (to_string(split));
}

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
		if (split[i])
			free(split[i]);
		i--;
	}
	free(split);
}

//		blabla$HOME bllabla
char	*transform_str(char *str, int status)
{
	int		i;
	char	**split;
	char	*env;
	char	*ret;
	char	*lop;
	t_split *test;
	
	test = get_str(str, ft_strlen(str));
	lop = change_str(test, status);
	printf("%s\n", lop);
	exit(1);
	return (ret);
}
