/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envgeter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:40:57 by bclerc            #+#    #+#             */
/*   Updated: 2022/01/14 15:52:25 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_split	*find_start(t_split *start)
{
	while (start->next && start->next->value != ' ' && start->next->value != '$'
		&& start->next->value != '"')
		start = start->next;
	return (start);
}

void
	switch_list(t_split **start, t_split **next, t_split **end, t_split **tmp)
{
	*start = (*tmp)->next;
	if ((*start)->value != '?')
		*start = find_start(*start);
	*next = (*start)->next;
	(*start)->next = NULL;
	*end = *start;
	*start = (*tmp)->next;
	free(*tmp);
}

char	*change_str(t_split *split, int status)
{
	t_split	*tmp;
	t_split	*start;
	t_split	*next;
	t_split	*last;

	start = NULL;
	tmp = split;
	last = tmp;
	while (tmp)
	{
		if (tmp->value == '$' && tmp->next && tmp->next->value != ' '
			&& last->value != '\'')
		{
			switch_list(&start, &next, (t_split *[1]){(&(t_split){})}, &tmp);
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

char	*transform_str(char *str, int status)
{
	t_split	*test;
	char	*ret;
	int		i;

	ret = 0;
	test = get_str(str, ft_strlen(str));
	ret = change_str(test, status);
	printf("Retour de commande  %s \n", ret);
	i = 0;
	while (ret[i])
	{
		if (ret[i] != ' ')
			return (ret);
		i++;
	}
	free(ret);
	return (NULL);
}
