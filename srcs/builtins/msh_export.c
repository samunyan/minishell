/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:43:59 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/12/07 16:36:07 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_export(t_list *envars)
{
	t_list	*current;

	current = envars;
	while (current)
	{
		((t_envar *)(current->content))->export = 0;
		current = current->next;
	}
}

static int	export_no_arg(void)
{
	int		i;
	int		len;
	char	**sorted;
	t_list	*envars;

	envars = g_envars;
	reset_export(envars);
	len = size_list(envars);
	sorted = ft_malloc(sizeof(char *) * (len + 1));
	if (!sorted)
		return (0);
	i = 0;
	while (i < len)
	{
		if (!find_min_env(envars, sorted, i))
		{
			clear_sorted(sorted, len + 1);
			return (0);
		}
		if (ft_strncmp(sorted[i], "declare -x PIPESTATUS=", 22))
			write(STDOUT_FILENO, sorted[i], ft_strlen(sorted[i]));
		i++;
	}
	clear_sorted(sorted, len + 1);
	return (1);
}

static int	export_arg(t_cmd *cmd)
{
	t_list	*new;
	int		i;
	t_envar	*var;

	var = str_to_envar((cmd->cmd)[1]);
	if (ft_strcmp(var->name, "PIPESTATUS") == 0)
	{
		free_envar(var);
		return (1);
	}
	free_envar(var);
	i = 1;
	while ((cmd->cmd)[i])
	{
		new = add_envar_export(&g_envars, (cmd->cmd)[i]);
		if (!new)
			return (0);
		i++;
	}
	return (1);
}

int	msh_export(t_cmd *cmd)
{
	if (!((cmd->cmd)[1]))
	{
		if (!export_no_arg())
			return (EXIT_FAILURE);
	}
	else
	{
		if (!export_arg(cmd))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
