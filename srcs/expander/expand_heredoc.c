/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <gscarama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:35:19 by gscarama          #+#    #+#             */
/*   Updated: 2022/12/02 15:07:02 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_heredoc(char **text, t_list *env)
{
	int		row;
	char	*param;

	row = 0;
	while (text[row] != NULL)
	{
		while (is_squote(&text[row]) != true
			&& locate_dollar(text[row]) != -2)
		{
			param = dollar_str(text[row]);
			if (param == NULL)
			{
				free(*text);
				*text = NULL;
				return (-1);
			}
			if (expd(text, env, param) == false)
				return (-1);
			free(param);
		}
		row++;
	}
	return (1);
}
