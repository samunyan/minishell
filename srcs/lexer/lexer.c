/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:04:01 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/12/07 16:42:50 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex(char c, int *i, size_t len, t_list **list)
{
	int						j;
	static t_lex_dispatch	arr[7]
		= {{C_QUOTE, lex_squote},
	{C_DQUOTE, lex_dquote},
	{C_SPACE, lex_space},
	{C_TAB, lex_space},
	{C_GREATER, lex_greater},
	{C_LESS, lex_less},
	{C_PIPE, lex_pipe}};

	j = 0;
	while (j < 7)
	{
		if (c == arr[j].c)
		{
			if (arr[j].f(c, i, len, list) == 0)
				return (0);
			return (1);
		}
		j++;
	}
	if (lex_char(c, i, len, list) == 0)
		return (0);
	return (1);
}

t_list	*lexer(char *input)
{
	t_list	*tok_list;
	size_t	input_len;
	int		i;

	input_len = ft_strlen(input) + 1;
	i = -1;
	if (!tok_list_init(&tok_list, input_len))
		return (NULL);
	while (1)
	{
		if (*input == C_NULL)
		{
			if (!lex_null(*input, &i, input_len, &tok_list))
				return (NULL);
			break ;
		}
		else
		{
			if (!lex(*input, &i, input_len, &tok_list))
				return (NULL);
		}
		input++;
	}
	return (tok_list);
}
