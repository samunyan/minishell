/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitcode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <gscarama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:15:46 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/24 13:57:06 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	init_exitcode(void)
{
	t_list	*node;
	t_envar	*pipestatus;

	node = add_envar("PIPESTATUS");
	if (!node)
		return (false);
	pipestatus = get_t_envar(node);
	pipestatus->n = 0;
	return (true);
}

void	update_exitcode(int exitcode)
{
	t_envar	*pipestatus;

	pipestatus = get_envar("PIPESTATUS");
	pipestatus->n = exitcode;
}

int	get_exitcode(void)
{
	t_envar	*pipestatus;

	pipestatus = get_envar("PIPESTATUS");
	return (pipestatus->n);
}
