/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <gscarama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:16:58 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/24 13:56:49 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_outfile(t_redir *redir)
{
	int	fd;

	fd = open(redir->out, O_WRONLY | O_CREAT | O_CLOEXEC | O_TRUNC, 0666);
	if (fd == -1)
	{
		msh_error(strerror, errno, redir->out);
		return (0);
	}
	if (dup2_and_close_oldfd(fd, STDOUT_FILENO) == -1)
		return (0);
	return (1);
}

static int	append_outfile(t_redir *redir)
{
	int	fd;

	fd = open(redir->out, O_WRONLY | O_CREAT | O_CLOEXEC | O_APPEND, 0666);
	if (fd == -1)
	{
		msh_error(strerror, errno, redir->out);
		return (0);
	}
	if (dup2_and_close_oldfd(fd, STDOUT_FILENO) == -1)
		return (0);
	return (1);
}

int	redir_out(t_redir *redir, int *new_fd_is_set)
{
	if (redir->type_redir == REDIR_OUT && redir->type_out == CREATE_OUTFILE)
	{
		if (!create_outfile(redir))
			return (0);
		*new_fd_is_set = 1;
	}
	else if (redir->type_redir == REDIR_OUT \
				&& redir->type_out == APPEND_OUTFILE)
	{
		if (!append_outfile(redir))
			return (0);
		*new_fd_is_set = 1;
	}
	return (1);
}
