/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export_noarg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:22:59 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/12/07 16:37:04 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_list(t_list *list)
{
	t_list	*current;
	int		i;

	current = list;
	if (!list)
		return (0);
	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

static void	*envar_to_str_export(void *envar)
{
	char	*ret;
	t_envar	*cast;

	cast = (t_envar *)envar;
	ret = ft_strjoin(cast->name, "=");
	if (!ret)
		return (NULL);
	if (cast->value)
	{
		ft_strappend(&ret, "\"");
		ft_strappend(&ret, cast->value);
		ft_strappend(&ret, "\"");
	}
	return (ret);
}

static char	*append_env_export(t_envar *envar)
{
	char	*str;

	str = (char *)envar_to_str_export(envar);
	if (!str)
		return (NULL);
	ft_strappend(&str, "\n");
	ft_strprepend(&str, "declare -x ");
	return (str);
}

int	find_min_env(t_list *envars, char **sorted, int i)
{
	t_list	*current;
	t_list	*min;

	current = envars;
	while (((t_envar *)(current->content))->export)
		current = current->next;
	min = current;
	current = current->next;
	while (current && ((t_envar *)(current->content))->export)
		current = current->next;
	while (current)
	{
		if (ft_strcmp(((t_envar *)(current->content))->name,
			((t_envar *)(min->content))->name) < 0
			&& !(((t_envar *)(current->content))->export))
			min = current;
		current = current->next;
	}
	((t_envar *)(min->content))->export = 1;
	sorted[i] = append_env_export((t_envar *)(min->content));
	if (!sorted[i])
		return (0);
	return (1);
}

void	clear_sorted(char **sorted, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(sorted[i]);
		sorted[i] = NULL;
		i++;
	}
	free(sorted);
}
