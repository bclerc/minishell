/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:19:43 by user42            #+#    #+#             */
/*   Updated: 2021/10/28 16:07:39 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_parse_echo(t_arg *arg, char **cpy, int i, t_cmd *cmd)
{
	int	j;
	int	tmp_nb;
	t_cmd	*tmp;
	t_cmd	*new;

	j = 0;
	tmp_nb = i;
	tmp = cmd;
	while (cmd != NULL && cmd->next != NULL)
		cmd = cmd->next;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	while (cpy[tmp_nb])
		tmp_nb++;
	new->cpy_nb = tmp_nb;
	new->nb = i;
	new->cmd = ft_strdup(cpy[j]);
	j++;
	if (cpy[j])
	{
		if (ft_strncmp(cpy[j], "-n", 2) == 0)
		{
			new->spec = ft_check_n(cpy, cmd, j);
			j++;
			if (cpy[j])
				new->msg = ft_cpy_msg(arg, cpy, i, j, new);
			else if (!cpy[j])
			{
				new->msg = NULL;
				new->next = NULL;
				if (tmp == NULL)
					tmp = new;
				else
					cmd->next = new;
				printf("echo1 : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d j = %d\n", cmd->nb, cmd->cmd, cmd->spec, cmd->msg, cmd->std, j);
				return (tmp);
			}
		}
		else
		{
			new->spec = NULL;
			new->msg = ft_cpy_msg(arg, cpy, i, j, new);
		}	
	}
	if (i == arg->count - 1)
		new->std = 0;
	else if (i < arg->count)
		new->std = ft_std(arg, cmd, i + 1);
			puts("che");
	printf("echo2 : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d j = %d\n", new->nb, new->cmd, new->spec, new->msg, new->std, j);
	//printf("echo2 : nb = %d, cmd = %s, spec = %s, msg = %s, std = %d j = %d\n", new->nb, new->cmd, new->spec, new->msg, new->std, j);
	printf("%p\n", &new);
	new->next = NULL;
	if (tmp == NULL)
		tmp = new;
	else
		cmd->next = new;

	return (tmp);
}

char	*ft_check_n(char **cpy, t_cmd *cmd, int i)
{
	int j;
	char	*tmp;

	j = 1;
	while (cpy[i][j])
	{
		if (cpy[i][j] != 'n')
			ft_print("Error in specification\n", -1);
			// + faire une fct qui sort 
		j++;
	}
	tmp = "-n";
	//cmd->spec = "-n";
	return (tmp);
}