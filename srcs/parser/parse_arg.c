/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:30:38 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/11/28 11:58:04 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_arg(t_list **tok_list, t_pars_data *data)
{
	t_token	*token;

	(void)tok_list;
	token = (t_token *)((data->current_tok)->content);
	(data->cmd)->cmd[data->i] = ft_strdup(token->text);
	if (!((data->cmd)->cmd[data->i]))
		return (0);
	data->current_tok = data->current_tok->next;
	data->i++;
	return (1);
}
