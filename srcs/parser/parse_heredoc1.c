/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:32:38 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/12/07 17:03:51 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_redir_heredoc(t_token *token, t_list *redirection)
{
	t_redir	*redir;

	redir = ((t_redir *)(redirection->content));
	redir->type_redir = REDIR_IN;
	redir->type_in = HEREDOC;
	free(redir->heredoc_delim);
	redir->heredoc_delim = ft_strdup(token->text);
	if (!(redir->heredoc_delim))
		return (0);
	free(redir->in);
	redir->in = NULL;
	return (1);
}

static int	create_redir_heredoc(t_token *token, t_pars_data *data)
{
	if (!create_redir(data))
		return (0);
	if (!fill_redir_heredoc(token, (data->cmd)->redirections))
		return (0);
	return (1);
}

static int	add_redir_heredoc(t_token *token, t_pars_data *data)
{
	t_list	*new;

	new = redir_init();
	if (!new)
		return (0);
	ft_lstadd_back(&((data->cmd)->redirections), new);
	if (!fill_redir_heredoc(token, (data->cmd)->redirections))
		return (0);
	return (1);
}

static int	parse_redir_error(char *text)
{
	if (!*text)
		msh_error(msh_strerror, ERRNUM_SYNTAX, "newline");
	else
		msh_error(msh_strerror, ERRNUM_SYNTAX, text);
	return (258);
}

int	parse_heredoc(t_list **tok_list, t_pars_data *data)
{
	t_token	*token;

	(void)tok_list;
	data->current_tok = (data->current_tok)->next;
	token = (t_token *)((data->current_tok)->content);
	if (!*token->text || (word_is_operator(token)))
		return (parse_redir_error(token->text));
	else if (!((data->cmd)->redirections))
	{
		if (!create_redir_heredoc(token, data))
			return (0);
	}
	else
	{
		if (!add_redir_heredoc(token, data))
			return (0);
	}
	if (!gather_heredoc(tok_list, data))
		return (0);
	data->current_tok = (data->current_tok)->next;
	return (1);
}
