/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envars_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:08:21 by samunyan          #+#    #+#             */
/*   Updated: 2022/12/07 18:08:22 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envar(void *var)
{
	t_envar	*cast;

	cast = var;
	free(cast->name);
	free(cast->value);
	free(var);
	var = NULL;
}

char	*msh_getenv(char *name)
{
	t_envar	*var;
	t_list	*list;

	list = g_envars;
	while (list)
	{
		var = get_t_envar(list);
		if (ft_strncmp(name, var->name, ft_strlen(name)) == 0)
			return (var->value);
		list = list->next;
	}
	return (NULL);
}

t_envar	*get_t_envar(t_list *node)
{
	return ((t_envar *)(node->content));
}

t_list	*find_envar(char *name)
{
	t_list	*list;

	list = g_envars;
	while (list)
	{
		if (ft_strcmp(name, ((t_envar *)(list->content))->name) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}
