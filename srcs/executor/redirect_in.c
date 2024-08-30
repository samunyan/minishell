/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:42:08 by samunyan          #+#    #+#             */
/*   Updated: 2022/12/07 17:42:09 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_heredoc(t_redir *redir)
{
	int		pfd[2];
	char	*input;

	input = redir->in;
	if (pipe(pfd) < 0)
	{
		msh_error(strerror, errno, "pipe in redir_heredoc");
		return (-1);
	}
	if (input && write(pfd[WRITE], input, ft_strlen(input)) == -1)
	{
		msh_error(strerror, errno, "write in redir_heredoc");
		close(pfd[WRITE]);
		return (-1);
	}
	close(pfd[WRITE]);
	return (pfd[READ]);
}

static int	create_infile(t_redir *redir)
{
	int	fd;

	fd = open(redir->in, O_RDONLY);
	if (fd == -1)
	{
		msh_error(strerror, errno, redir->in);
		return (0);
	}
	if (dup2_and_close_oldfd(fd, STDIN_FILENO) == -1)
		return (0);
	return (1);
}

static int	create_heredoc(t_redir *redir)
{
	int	fd;

	fd = redir_heredoc(redir);
	if (fd == -1)
	{
		msh_error(strerror, errno, "heredoc file");
		return (0);
	}
	if (dup2_and_close_oldfd(fd, STDIN_FILENO) == -1)
		return (0);
	return (1);
}

int	redir_in(t_redir *redir, int *new_fd_is_set)
{
	if (redir->type_redir == REDIR_IN && redir->type_in == INFILE)
	{
		if (!create_infile(redir))
			return (0);
		*new_fd_is_set = 1;
	}
	else if (redir->type_redir == REDIR_IN && redir->type_in == HEREDOC)
	{
		if (!create_heredoc(redir))
			return (0);
		*new_fd_is_set = 1;
	}
	return (1);
}
