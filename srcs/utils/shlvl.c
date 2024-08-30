/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <gscarama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:51:53 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/24 13:57:09 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	update_shlvl(void)
{
	t_envar	*shlvl;
	int		v;

	shlvl = get_envar("SHLVL");
	if (shlvl)
	{
		v = ft_atoi(shlvl->value) + 1;
		free(shlvl->value);
		shlvl->value = NULL;
		shlvl->value = ft_itoa(v);
		if (!shlvl->value)
			return (false);
		shlvl->n = v;
	}
	else
	{
		if (!add_envar("SHLVL=1"))
			return (false);
		shlvl = get_envar("SHLVL");
		shlvl->n = 1;
	}
	return (true);
}
