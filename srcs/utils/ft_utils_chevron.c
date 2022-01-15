/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_chevron.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 10:33:04 by asgaulti          #+#    #+#             */
/*   Updated: 2022/01/14 10:46:42 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_chevron(t_arg *arg, t_cmd *cmd)
{
	t_redir	*redir;
	int		exist;

	cmd->redir = NULL;
	exist = ft_special_exist(arg);
	printf("e %d\n", exist);
	// arg->i = ft_check_redir(arg, arg->i);
	// while (arg->i < arg->count)
	// {
	// 	if (arg->i % 2 != 0)
	// 	{
	// 		creer un maillon de redir
	// 		checker quels std sont presents (ft_exist_special)
	// 		si in uniquement : aller au bout de arg->i et prendre le dernier et sortir 
	// 		si out uniquement : tq arg->i < arg->count creer maillons out 
	// 		si les deux : creer le premier maillon avec le dernier in puis y ajouter le premier out 
	// 		et si encore des > creer maillons suivants
	// 		les std sont les arg->cmds[arg->i - 1]
	// 		les fd_out ou in sont arg->cmds[arg->i]
			
	// 	}
	// }
	return (cmd);
}

int	ft_special_exist(t_arg *arg)
{
	int	exist;
	int	i;

	i = arg->i;
	while (i < arg->count)
	{
		if (!ft_strcmp(arg->cmds[i], "<") || !ft_strcmp(arg->cmds[i], "<<"))
		{
			if (!exist)
				exist = 1;
			else if (exist == 2)
				exist = 3;
		}
		else if (!ft_strcmp(arg->cmds[i], ">") || !ft_strcmp(arg->cmds[i], ">>"))
		{
			if (!exist)
				exist = 2;
			else if (exist == 1)
				exist = 3;
		}
		i++;
	}
	return (exist);
}
