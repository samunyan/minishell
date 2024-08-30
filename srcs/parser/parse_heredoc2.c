/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:00:05 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/12/07 17:07:08 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_input_for_heredoc(t_redir *redir, char *delim)
{
	char	*line;

	while (1)
	{
		errno = 0;
		line = readline(PS2);
		if (!line || ft_strcmp(line, delim) == 0)
		{
			if (errno == ENOMEM)
			{
				msh_error(strerror, errno, "readline");
				return (0);
			}
			free(line);
			break ;
		}
		if (!ft_strappend(&redir->in, line) || !ft_strappend(&redir->in, "\n"))
		{
			free(line);
			return (0);
		}
		free(line);
	}
	return (1);
}

char	*heredoc_to_string(int fd, int *error)
{
	char	*line;
	char	*result;

	line = NULL;
	result = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_strappend(&result, line))
		{
			free(line);
			*error = 1;
			return (NULL);
		}
		free(line);
	}
	return (result);
}

static int	parent_gather_heredoc(int pfd[2], t_redir *redir)
{
	int	wstatus;
	int	error;

	signal(SIGINT, SIG_IGN);
	close(pfd[WRITE]);
	wait(&wstatus);
	signal(SIGINT, handle_sigint);
	error = get_exitcode_from_child(wstatus);
	if (!error)
		redir->in = heredoc_to_string(pfd[READ], &error);
	close(pfd[READ]);
	return (error == 0);
}

static int	child_gather_heredoc(int pfd[2], t_redir *redir, t_pars_data *data,
	t_list **tok_list)
{
	int		error;
	char	*tmp_delim;

	signal(SIGINT, SIG_DFL);
	close(pfd[READ]);
	error = 0;
	if (is_double_quoted(redir->heredoc_delim))
	{
		tmp_delim = get_delim_without_quotes(redir->heredoc_delim);
		if (!tmp_delim || !get_input_for_heredoc(redir, tmp_delim))
			error = 1;
		free(tmp_delim);
	}
	else if (!get_input_for_heredoc(redir, redir->heredoc_delim))
		error = 1;
	if (!error && redir->in)
		write(pfd[WRITE], redir->in, ft_strlen(redir->in));
	close(pfd[WRITE]);
	ft_lstclear(tok_list, clear_token);
	ft_lstclear(&(data->cmd_list), clear_cmd);
	free(data);
	return (error);
}

int	gather_heredoc(t_list **tok_list, t_pars_data *data)
{
	int		pfd[2];
	pid_t	pid;
	t_redir	*redir;

	redir = ((t_redir *)(data->cmd->redirections->content));
	if (pipe(pfd) == -1)
		return (0);
	pid = fork();
	if (pid)
	{
		if (pid < 0)
		{
			close(pfd[WRITE]);
			close(pfd[READ]);
			return (0);
		}
		return (parent_gather_heredoc(pfd, redir));
	}
	else
		exit(child_gather_heredoc(pfd, redir, data, tok_list));
}
