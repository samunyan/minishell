/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:41:28 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/11/22 11:47:15 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_space(char c, int *i, size_t len, t_list **list)
{
	t_token	*token;

	(void)len;
	token = (t_token *)(ft_lstlast(*list)->content);
	if ((token->flag & W_QUOTED) || (token->flag & W_DQUOTED))
		token->text[++(*i)] = c;
	else if (*i >= 0)
		token->text[++(*i)] = C_NULL;
	return (1);
}
