/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:55:07 by astrid            #+#    #+#             */
/*   Updated: 2021/10/30 11:22:13 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*ft_redir(t_arg *arg, char **cpy, t_cmd *cmd, t_redir *redir)
{
	cmd->redir = cmd->next;
	printf("redir_std = %d\n", redir->std_redir);
	// stocker la cmd suivant les chevrons (msg et std) 
	// + checker la cmd suiv : si chevron next pointe sur nouveau maillon de redir
	// si pipe next repointe sur cmd
	// si null next pointe sur null
	return (redir);
}