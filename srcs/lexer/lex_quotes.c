/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:38:10 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/12/07 16:44:35 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_token(t_token *token, char c, int *i, int flag)
{
	token->text[++(*i)] = c;
	token->flag |= flag;
}

static void	unquote(t_token *token, char c, int *i, int flag)
{
	token->text[++(*i)] = c;
	if (token->flag & flag)
			token->flag &= ~flag;
}

int	lex_squote(char c, int *i, size_t len, t_list **list)
{
	t_token	*token;

	(void)len;
	token = (t_token *)(ft_lstlast(*list)->content);
	if (token->flag & W_QUOTED || token->flag & W_DQUOTED)
		unquote(token, c, i, W_QUOTED);
	else if (*i >= 0 && token->text[*i] != C_NULL && !(token->flag & W_GREATER)
		&& !(token->flag & W_LESS))
		write_token(token, c, i, W_QUOTED);
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
		write_token(token, c, i, W_QUOTED);
	}
	return (1);
}

int	lex_dquote(char c, int *i, size_t len, t_list **list)
{
	t_token	*token;

	(void)len;
	token = (t_token *)(ft_lstlast(*list)->content);
	if (token->flag & W_QUOTED || token->flag & W_DQUOTED)
		unquote(token, c, i, W_DQUOTED);
	else if (*i >= 0 && token->text[*i] != C_NULL && !(token->flag & W_GREATER)
		&& !(token->flag & W_LESS))
		write_token(token, c, i, W_DQUOTED);
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
		write_token(token, c, i, W_DQUOTED);
	}
	return (1);
}
