/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <gscarama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:23:22 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/24 13:56:52 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_exitcode_from_child(int wstatus)
{
	if (WIFSIGNALED(wstatus))
	{
		if (WTERMSIG(wstatus) == 2)
			ft_putstr_fd("\n", STDOUT_FILENO);
		else if (WTERMSIG(wstatus) == 3)
			ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
		return (WTERMSIG(wstatus) + 128);
	}
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	return (EXIT_FAILURE);
}

void	execute(t_list *cmd_list)
{
	char	**envp;

	envp = list_to_str_arr(g_envars, envar_to_str);
	if (!envp)
	{
		update_exitcode(EXIT_FAILURE);
		return ;
	}
	if (ft_lstsize(cmd_list) == 1)
		do_simple_command(cmd_list, envp);
	else
		do_pipeline(cmd_list, envp);
	ft_free_arr((void **)envp);
}
