/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 21:24:41 by elsajoo-tho       #+#    #+#             */
/*   Updated: 2022/11/28 15:58:52 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_redir_in(t_token *token, t_list *redirection)
{
	t_redir	*redir;

	redir = (t_redir *)((redirection)->content);
	redir->type_redir = REDIR_IN;
	redir->type_in = INFILE;
	free(redir->in);
	redir->in = ft_strdup(token->text);
	if (!(redir->in))
		return (0);
	return (1);
}

static int	create_redir_input(t_token *token, t_pars_data *data)
{
	if (!create_redir(data))
		return (0);
	if (!fill_redir_in(token, (data->cmd)->redirections))
		return (0);
	return (1);
}

static int	add_redir_input(t_token *token, t_pars_data *data)
{
	t_list	*new;

	new = redir_init();
	if (!new)
		return (0);
	ft_lstadd_back(&((data->cmd)->redirections), new);
	if (!fill_redir_in(token, new))
		return (0);
	return (1);
}

int	parse_input(t_list **tok_list, t_pars_data *data)
{
	t_token	*token;

	(void)tok_list;
	data->current_tok = (data->current_tok)->next;
	token = (t_token *)((data->current_tok)->content);
	if (!*token->text || (word_is_operator(token)))
	{
		if (!*token->text)
			msh_error(msh_strerror, ERRNUM_SYNTAX, "newline");
		else
			msh_error(msh_strerror, ERRNUM_SYNTAX, token->text);
		return (258);
	}
	else if (!((data->cmd)->redirections))
	{
		if (!create_redir_input(token, data))
			return (0);
	}
	else
	{
		if (!add_redir_input(token, data))
			return (0);
	}
	data->current_tok = (data->current_tok)->next;
	return (1);
}
