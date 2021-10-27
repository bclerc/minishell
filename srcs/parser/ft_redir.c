/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astrid <astrid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:55:07 by astrid            #+#    #+#             */
/*   Updated: 2021/10/27 17:04:18 by astrid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*ft_redir(t_arg *arg, char **cpy, int i, t_cmd *cmd, t_redir *redir)
{
	cmd->next = cmd->redir;
	// stocker la cmd suivant les chevrons (msg et std) 
	// + checker la cmd suiv : si chevron next pointe sur nouveau maillon de redir
	// si pipe next repointe sur cmd
	// si null next pointe sur null
	return (redir);
}