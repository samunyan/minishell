/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envars_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:08:27 by samunyan          #+#    #+#             */
/*   Updated: 2022/12/07 18:08:29 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envar	*get_envar(char *name)
{
	t_list	*list;

	list = g_envars;
	while (list)
	{
		if (ft_strcmp(name, ((t_envar *)(list->content))->name) == 0)
			return (get_t_envar(list));
		list = list->next;
	}
	return (NULL);
}

t_list	*init_envars_list(char *env[], t_list **envars)
{
	*envars = str_arr_to_list(env, str_to_envar);
	if ((!find_envar("PIPESTATUS") && !init_exitcode())
		|| !update_shlvl())
	{
		ft_lstclear(envars, free_envar);
		return (NULL);
	}
	return (*envars);
}

t_list	*add_envar(char *name_equal_value)
{
	t_list	*new;
	t_envar	*envar;

	envar = str_to_envar(name_equal_value);
	if (!envar)
		return (NULL);
	new = ft_lstnew(envar);
	if (!new)
	{
		free_envar(envar);
		return (NULL);
	}
	ft_lstadd_back(&g_envars, new);
	return (new);
}
