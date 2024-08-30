/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:57:05 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/11/22 15:32:23 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_pipe(char c, int *i, size_t len, t_list **list)
{
	t_token	*token;

	token = (t_token *)(ft_lstlast(*list)->content);
	if ((token->flag & W_QUOTED) || (token->flag & W_DQUOTED))
		token->text[++(*i)] = c;
	else
	{
		if (*i >= 0)
		{
			dollar_flag(token);
			if (!add_token(len, list))
				return (0);
			token = (t_token *)(ft_lstlast(*list)->content);
			*i = -1;
		}
		token->text[++(*i)] = C_PIPE;
		token->text[++(*i)] = C_NULL;
		token->flag |= W_PIPE;
	}
	return (1);
}
