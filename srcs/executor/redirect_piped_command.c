/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_piped_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:42:38 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/30 17:42:40 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_in_piped_command(t_cmd *cmd, int **pipes)
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
	if (!new_fd_is_set)
		if (cmd->i_child != 0)
			if (dup2_and_close_oldfd(pipes[cmd->i_child - 1][READ], \
			STDIN_FILENO) == -1)
				return (0);
	return (1);
}

static int	arrsize(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static int	set_out_piped_command(t_cmd *cmd, int **pipes_fd)
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
	if (!new_fd_is_set)
	{
		if (cmd->i_child != arrsize((void **)pipes_fd))
			if (dup2_and_close_oldfd(pipes_fd[cmd->i_child][WRITE], \
			STDOUT_FILENO) == -1)
				return (0);
	}
	return (1);
}

int	set_io_piped_command(t_cmd *cmd, int **pipes)
{
	int	error;

	error = 0;
	if (!set_in_piped_command(cmd, pipes) || !set_out_piped_command(cmd, pipes))
		error = 1;
	if (pipes)
	{
		close_pipes(pipes);
		ft_free_arr((void **)pipes);
	}
	return (error);
}
