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

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
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
	if (!(*alst))
	{
		*alst = new;
		//puts("guevara");
		return ;
	}
		//puts("che");
	while (last->next)
		last = last->next;
	last->next = new;
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char *copy_s;

	copy_s = s;
	while (n > 0)
	{
		*copy_s++ = '\0';
		n--;
	}
}
