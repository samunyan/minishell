/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_null.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:54:00 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/12/07 16:45:11 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_null(char c, int *i, size_t len, t_list **list)
{
	t_token	*token;

	(void) c;
	token = (t_token *)(ft_lstlast(*list)->content);
	if (*i >= 0)
	{
		dollar_flag(token);
		if (!add_token(len, list))
			return (0);
		token = (t_token *)(ft_lstlast(*list)->content);
		*i = -1;
	}
	token->flag |= W_NULL;
	return (1);
}
