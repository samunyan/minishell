/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:32:52 by dsoroko           #+#    #+#             */
/*   Updated: 2022/12/07 16:32:11 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_without_flag(t_cmd	*cmd)
{
	int	i;

	i = 1;
	while (cmd->cmd[i])
	{
		write(1, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
		if (cmd->cmd[i + 1])
			write(1, " ", 1);
		++i;
	}
	write(1, "\n", 1);
}

static void	echo_with_flag(t_cmd *cmd)
{
	int	i;

	i = 2;
	while (cmd->cmd[i] && !ft_strncmp(cmd->cmd[i], "-n", 2))
		++i;
	while (cmd->cmd[i])
	{
		write(1, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
		if (cmd->cmd[i + 1])
			write(1, " ", 1);
		++i;
	}
}

static int	arrsize(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	msh_echo(t_cmd *cmd)
{
	int	len;

	len = arrsize((void **)cmd->cmd);
	if (len == 1)
		write(1, "\n", 1);
	if (len > 1 && ft_strcmp(cmd->cmd[1], "-n") != 0)
		echo_without_flag(cmd);
	if (len > 2 && ft_strcmp(cmd->cmd[1], "-n") == 0)
		echo_with_flag(cmd);
	return (EXIT_SUCCESS);
}
