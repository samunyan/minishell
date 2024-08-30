/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_append.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 20:44:37 by elsajoo-tho       #+#    #+#             */
/*   Updated: 2022/11/28 12:03:32 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_redir_append(t_token *token, t_pars_data *data)
{
	if (!create_redir(data))
		return (0);
	if (!fill_redir_out(APPEND_OUTFILE, token, (data->cmd)->redirections))
		return (0);
	return (1);
}

static int	add_redir_append(t_token *token, t_pars_data *data)
{
	t_list	*new;

	new = redir_init();
	if (!new)
		return (0);
	ft_lstadd_back(&((data->cmd)->redirections), new);
	if (!fill_redir_out(APPEND_OUTFILE, token, new))
		return (0);
	return (1);
}

int	parse_append(t_list **tok_list, t_pars_data *data)
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
		if (!create_redir_append(token, data))
			return (0);
	}
	else
	{
		if (!add_redir_append(token, data))
			return (0);
	}
	data->current_tok = (data->current_tok)->next;
	return (1);
}
