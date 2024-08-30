/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:19:41 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/12/07 16:44:13 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_dgreater(t_token *token, int *i)
{
	token->text[++(*i)] = C_GREATER;
	token->text[++(*i)] = C_NULL;
	token->flag &= ~W_GREATER;
	token->flag |= W_GREATERGREATER;
	return (1);
}

int	lex_greater(char c, int *i, size_t len, t_list **list)
{
	t_token	*token;

	token = (t_token *)(ft_lstlast(*list)->content);
	if ((token->flag & W_QUOTED) || (token->flag & W_DQUOTED))
		token->text[++(*i)] = c;
	else
	{
		if ((token->flag & W_GREATER) && token->text[*i] != C_NULL)
			lex_dgreater(token, i);
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
			token->text[++(*i)] = c;
			token->flag |= W_GREATER;
		}
	}
	return (1);
}

int	lex_dless(t_token *token, int *i)
{
	token->text[++(*i)] = C_LESS;
	token->text[++(*i)] = C_NULL;
	token->flag &= ~W_LESS;
	token->flag |= W_LESSLESS;
	return (1);
}

int	lex_less(char c, int *i, size_t len, t_list **list)
{
	t_token	*token;

	token = (t_token *)(ft_lstlast(*list)->content);
	if ((token->flag & W_QUOTED) || (token->flag & W_DQUOTED))
		token->text[++(*i)] = c;
	else
	{
		if ((token->flag & W_LESS) && token->text[*i] != C_NULL)
			lex_dless(token, i);
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
			token->text[++(*i)] = c;
			token->flag |= W_LESS;
		}
	}
	return (1);
}
