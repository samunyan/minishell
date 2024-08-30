/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:03:18 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/12/07 13:50:00 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*replace_envar_value(t_list **list, t_envar *envar)
{
	t_list	*current;

	current = *list;
	while (current)
	{
		if (!(ft_strcmp(((t_envar *)(current->content))->name, envar->name)))
		{
			((t_envar *)(current->content))->value = envar->value;
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

t_list	*add_envar_export(t_list **list, char *name_equal_value)
{
	t_list	*new;
	t_list	*current;
	t_envar	*envar;

	envar = str_to_envar(name_equal_value);
	if (!envar)
		return (NULL);
	if (!(*envar->name))
	{
		msh_error(msh_strerror, ERRNUM_EXPORT, name_equal_value);
		return (NULL);
	}
	current = replace_envar_value(list, envar);
	if (current)
		return (current);
	new = ft_lstnew(envar);
	if (!new)
		return (NULL);
	ft_lstadd_back(list, new);
	return (new);
}
