/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:30:31 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/12/07 16:49:35 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_is_operator(t_token *token)
{
	if ((token->flag & W_GREATER) || (token->flag & W_GREATERGREATER)
		|| (token->flag & W_LESS) || (token->flag & W_LESSLESS)
		|| (token->flag & W_PIPE))
		return (1);
	return (0);
}

int	parse_redir(t_list **tok_list, t_pars_data *data)
{
	t_token	*token;
	int		ret;

	token = (t_token *)((data->current_tok)->content);
	if (token->flag & W_GREATER)
		ret = parse_output(tok_list, data);
	else if (token->flag & W_GREATERGREATER)
		ret = parse_append(tok_list, data);
	else
		ret = parse_input(tok_list, data);
	return (ret);
}
