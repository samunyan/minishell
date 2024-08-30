/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <gscarama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:31:05 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/12/08 14:18:51 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_node_envar(void *content)
{
	t_envar	*envar;

	envar = (t_envar *)content;
	free(envar->name);
	envar->name = NULL;
	free(envar->value);
	envar->value = NULL;
	envar->n = 0;
	envar->export = 0;
	free(envar);
	envar = NULL;
}

static void	remove_node_env(t_list **envars, t_list *previous, t_list *current)
{
	if (!previous)
	{
		*envars = (*envars)->next;
		current->next = NULL;
		ft_lstdelone(current, clear_node_envar);
	}
	else if (!current->next)
	{
		previous->next = NULL;
		ft_lstdelone(current, clear_node_envar);
	}
	else
	{
		previous->next = current->next;
		current->next = NULL;
		ft_lstdelone(current, clear_node_envar);
	}
}

static void	remove_envar(t_list **envars, char *str)
{
	t_list	*current;
	t_list	*previous;

	current = *envars;
	previous = NULL;
	while (current)
	{
		if (!ft_strcmp(((t_envar *)(current->content))->name, str))
		{
			remove_node_env(envars, previous, current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

int	msh_unset(t_cmd *cmd)
{
	int	i;

	i = 1;
	while ((cmd->cmd)[i])
	{
		if (ft_strchr((cmd->cmd)[i], '=') || ft_strchr((cmd->cmd)[i], '/'))
		{
			msh_error(msh_strerror, ERRNUM_EXPORT, (cmd->cmd)[i]);
			return (EXIT_FAILURE);
		}
		if (!ft_strcmp((cmd->cmd)[i], "PIPESTATUS"))
			break ;
		remove_envar(&g_envars, (cmd->cmd)[i++]);
	}
	return (EXIT_SUCCESS);
}
