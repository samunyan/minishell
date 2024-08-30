/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:53:40 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/11/22 15:31:33 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_char(char c, int *i, size_t len, t_list **list)
{
	t_token	*token;

	token = (t_token *)(ft_lstlast(*list)->content);
	if (token->flag & W_QUOTED || token->flag & W_DQUOTED)
		token->text[++(*i)] = c;
	else if (*i >= 0 && token->text[*i] != C_NULL && !(token->flag & W_GREATER)
		&& !(token->flag & W_LESS))
		token->text[++(*i)] = c;
	else
	{
		if ((*i >= 0 && token->text[*i] == C_NULL)
			|| (token->flag & W_GREATER || token->flag & W_LESS))
		{
			dollar_flag(token);
			if (!add_token(len, list))
				return (0);
			token = (t_token *)(ft_lstlast(*list)->content);
			*i = -1;
		}
		token->text[(++(*i))] = c;
	}
	return (1);
}
