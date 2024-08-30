/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:35:51 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/11/28 12:02:31 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*redir_init(void)
{
	t_redir	*redir;
	t_list	*redirections;

	redir = ft_malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redirections = ft_lstnew(redir);
	if (!redirections)
	{
		free(redir);
		return (NULL);
	}
	return (redirections);
}

t_cmd	*cmd_init(t_list **tok_list)
{
	t_cmd	*command;

	command = ft_malloc(sizeof(t_cmd));
	if (!command)
		return (NULL);
	command->cmd = ft_malloc(sizeof(char *) * (ft_lstsize(*tok_list) + 1));
	if (!(command->cmd))
	{
		free(command);
		return (NULL);
	}
	return (command);
}

t_list	*init_cmd_list(t_list **tok_list)
{
	t_cmd	*command;
	t_list	*cmd_list;

	command = cmd_init(tok_list);
	if (!command)
		return (NULL);
	cmd_list = ft_lstnew(command);
	if (!cmd_list)
		return (NULL);
	return (cmd_list);
}

t_pars_data	*init_data(t_list **tok_list)
{
	t_pars_data	*data;

	data = ft_malloc(sizeof(t_pars_data));
	if (!data)
		return (NULL);
	data->cmd_list = init_cmd_list(tok_list);
	data->current_tok = (*tok_list);
	data->cmd = (t_cmd *)((data->cmd_list)->content);
	data->i = 0;
	return (data);
}
