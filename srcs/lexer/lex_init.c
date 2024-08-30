/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:08:25 by elsajoo-tho       #+#    #+#             */
/*   Updated: 2022/12/07 16:45:44 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_init(size_t len)
{
	t_token	*token;

	token = ft_malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->text = ft_malloc(len);
	if (!token->text)
	{
		free (token);
		return (NULL);
	}
	token->flag = 0;
	return (token);
}

int	tok_list_init(t_list **list, size_t len)
{
	t_token	*token;

	token = token_init(len);
	if (!token)
		return (0);
	*list = ft_lstnew((void *)token);
	if (!(*list))
	{
		free (token->text);
		free (token);
		return (0);
	}
	return (1);
}
