/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 10:03:18 by asgaulti          #+#    #+#             */
/*   Updated: 2021/10/07 10:34:08 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print(char *str, int res)
{
	write (1, str, ft_strlen(str));
	return (res);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	int		i;
	char	*copy_s1;

	i = 0;
	copy_s1 = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!copy_s1)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		copy_s1[i] = (char)s1[i];
		i++;
	}
	copy_s1[i] = '\0';
	return (copy_s1);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list) * 1);
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *last;

	last = *alst;
	if (!alst)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	while (last->next)
		last = last->next;
	last->next = new;
}
