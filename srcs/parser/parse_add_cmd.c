/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_add_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:33:36 by samunyan          #+#    #+#             */
/*   Updated: 2022/12/07 17:14:04 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_input_for_cmd(char **buf)
{
	char	*line;

	while (!*buf)
	{
		errno = 0;
		line = readline(PS2);
		if (!line)
		{
			if (errno == ENOMEM)
			{
				msh_error(strerror, errno, "readline");
				return (1);
			}
			else
				break ;
		}
		if (*line && !ft_strappend(buf, line))
		{
			free(line);
			return (1);
		}
		free(line);
	}
	return (0);
}

static int	check_has_error(t_check *check)
{
	if (!check->arg || !check->heredoc || !check->pipe || !check->redir)
		return (1);
	if (check->heredoc == 258 || check->redir == 258 || check->pipe == 258)
		return (258);
	return (0);
}

static int	parse_cmd(t_pars_data **data, t_list *tok_list)
{
	t_check		check;
	int			error;

	error = 0;
	ft_memset(&check, 1, sizeof(t_check));
	while (!error)
	{
		if (word_is_redir(*data))
			check.redir = parse_redir(&tok_list, *data);
		else if (get_t_token((*data)->current_tok)->flag & W_LESSLESS)
			check.heredoc = parse_heredoc(&tok_list, *data);
		else if (get_t_token((*data)->current_tok)->flag & W_PIPE)
			check.pipe = parse_pipe(&tok_list, *data);
		else if (get_t_token((*data)->current_tok)->flag & W_NULL)
			break ;
		else
			check.arg = parse_arg(&tok_list, *data);
		error = check_has_error(&check);
	}
	return (error);
}

static t_pars_data	*prepare_data_to_parse(t_list **cmd_list, int *error)
{
	t_list		*tok_list;
	t_pars_data	*data;
	char		*buf;

	buf = NULL;
	*error = get_input_for_cmd(&buf);
	if (*error)
		return (NULL);
	if (!buf)
	{
		*error = 258;
		msh_error(msh_strerror, ERRNUM_SYNTAX_EOF, NULL);
		return (NULL);
	}
	tok_list = lexer(buf);
	free(buf);
	if (!tok_list)
		return (NULL);
	data = init_data(&tok_list);
	if (!data)
		return (NULL);
	free(data->cmd_list);
	data->cmd_list = *cmd_list;
	data->cmd = get_t_cmd(ft_lstlast(*cmd_list));
	return (data);
}

int	append_cmd(t_list **cmd_list)
{
	t_list		*tok_list;
	t_pars_data	*data;
	int			error;

	tok_list = NULL;
	data = prepare_data_to_parse(cmd_list, &error);
	if (!data)
	{
		ft_lstclear(&tok_list, clear_token);
		return (error);
	}
	tok_list = data->current_tok;
	error = parse_cmd(&data, tok_list);
	if (error)
		ft_lstclear(&(data->cmd_list), clear_cmd);
	ft_lstclear(&tok_list, clear_token);
	*cmd_list = data->cmd_list;
	free(data);
	return (error);
}
