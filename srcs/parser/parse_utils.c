/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:45:53 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/11/28 12:04:59 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_cmd_array(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
}

void	clear_cmd(void *ptr)
{
	t_cmd	*command;

	command = (t_cmd *)ptr;
	clear_cmd_array(command->cmd);
	ft_lstclear(&command->redirections, clear_redir);
}
