/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:46:19 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/12/07 16:48:56 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_is_redir(t_pars_data *data)
{
	t_token	*token;

	token = (t_token *)((data->current_tok)->content);
	if ((token->flag & W_GREATER) || (token->flag & W_GREATERGREATER)
		|| (token->flag & W_LESS))
		return (1);
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

t_list	*parser(t_list **tok_list)
{
	t_pars_data	*data;
	t_list		*cmd_list;
	int			error;

	data = init_data(tok_list);
	if (!data)
	{
		ft_lstclear(tok_list, clear_token);
		update_exitcode(EXIT_FAILURE);
		return (NULL);
	}
	error = parse_cmd(&data, *tok_list);
	if (error)
		ft_lstclear(&(data->cmd_list), clear_cmd);
	ft_lstclear(tok_list, clear_token);
	cmd_list = data->cmd_list;
	free(data);
	while (!error && get_t_cmd(ft_lstlast(cmd_list))->cmd[0] == NULL)
		error = append_cmd(&cmd_list);
	if (error)
	{
		update_exitcode(error);
		ft_lstclear(&cmd_list, clear_cmd);
	}
	return (cmd_list);
}
