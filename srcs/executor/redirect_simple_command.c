/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_simple_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:48:24 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/30 17:48:25 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_in_simple_command(t_cmd *cmd)
{
	t_redir	*redir;
	t_list	*tmp;
	int		new_fd_is_set;

	new_fd_is_set = 0;
	tmp = cmd->redirections;
	while (tmp)
	{
		redir = (t_redir *)(tmp)->content;
		if (!redir_in(redir, &new_fd_is_set))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

static int	set_out_simple_command(t_cmd *cmd)
{
	t_redir	*redir;
	t_list	*tmp;
	int		new_fd_is_set;

	new_fd_is_set = 0;
	tmp = cmd->redirections;
	while (tmp)
	{
		redir = (t_redir *)(tmp)->content;
		if (!redir_out(redir, &new_fd_is_set))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	set_io_simple_command(t_cmd *cmd, int saved_io[2])
{
	int	error;

	saved_io[0] = dup(STDIN_FILENO);
	if (saved_io[0] == -1)
	{
		ft_err_msg(strerror, errno, "dup in set_io_simple_command");
		return (1);
	}
	saved_io[1] = dup(STDOUT_FILENO);
	if (saved_io[1] == -1)
	{
		dup2_and_close_oldfd(saved_io[0], STDIN_FILENO);
		ft_err_msg(strerror, errno, "dup in set_io_simple_command");
		return (1);
	}
	error = 0;
	if (!set_in_simple_command(cmd) || !set_out_simple_command(cmd))
	{
		dup2_and_close_oldfd(saved_io[0], STDIN_FILENO);
		dup2_and_close_oldfd(saved_io[1], STDOUT_FILENO);
		error = 1;
	}
	return (error);
}
