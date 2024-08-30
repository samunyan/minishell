/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:23:27 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/12/07 16:50:40 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_pipe(t_list **tok_list, t_pars_data *data)
{
	t_list	*new;

	if (get_t_cmd(ft_lstlast(data->cmd_list))->cmd[0] == NULL)
	{
		msh_error(msh_strerror, ERRNUM_SYNTAX,
			get_t_token(data->current_tok)->text);
		return (258);
	}
	data->cmd = cmd_init(tok_list);
	new = ft_lstnew(data->cmd);
	if (!new)
		return (0);
	ft_lstadd_back(&data->cmd_list, new);
	data->current_tok = data->current_tok->next;
	data->i = 0;
	return (1);
}
