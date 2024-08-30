/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:00:11 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/12/07 16:43:10 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_token(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	free (token->text);
	token->text = NULL;
	free (token);
	token = NULL;
}

int	add_token(size_t len, t_list **list)
{
	t_token	*token;
	t_list	*node;

	token = token_init(len);
	if (!token)
	{
		ft_lstclear(list, clear_token);
		return (0);
	}
	node = ft_lstnew((void *)token);
	if (!node)
	{
		clear_token(token);
		ft_lstclear(list, clear_token);
		return (0);
	}
	ft_lstadd_back(list, node);
	return (1);
}

void	dollar_flag(t_token *token)
{
	if (token->text[0] != C_QUOTE && ft_strchr(token->text, C_DOLLAR))
		token->flag |= W_HASDOLLAR;
}
