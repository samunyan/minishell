/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_piped_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:40:13 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/30 17:40:14 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_piped_command(t_cmd *cmd, char **envp, int **pipes)
{
	int	error;

	error = set_io_piped_command(cmd, pipes);
	if (error)
	{
		free_cmd(cmd);
		ft_free_arr((void **)envp);
		ft_lstclear(&g_envars, free_envar);
		exit(EXIT_FAILURE);
	}
	error = execute_simple_command(cmd, envp);
	free_cmd(cmd);
	ft_free_arr((void **)envp);
	ft_lstclear(&g_envars, free_envar);
	close_stdio();
	exit(error);
}
