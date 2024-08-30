/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:29:05 by samunyan          #+#    #+#             */
/*   Updated: 2022/12/02 15:19:04 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_cmd *cmd)
{
	if (
		ft_strcmp(cmd->cmd[0], "echo") == 0
		|| ft_strcmp(cmd->cmd[0], "cd") == 0
		|| ft_strcmp(cmd->cmd[0], "pwd") == 0
		|| ft_strcmp(cmd->cmd[0], "export") == 0
		|| ft_strcmp(cmd->cmd[0], "unset") == 0
		|| ft_strcmp(cmd->cmd[0], "env") == 0
		|| ft_strcmp(cmd->cmd[0], "exit") == 0)
		return (true);
	return (false);
}

static int	arrsize(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	execute_builtin(t_cmd *cmd, char **envp)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		return (msh_exit(cmd, envp));
	if (ft_strcmp(cmd->cmd[0], "env") == 0)
		return (msh_env(envp));
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		return (msh_echo(cmd));
	if (ft_strcmp(cmd->cmd[0], "export") == 0)
		return (msh_export(cmd));
	if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		return (msh_unset(cmd));
	if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		return (msh_pwd());
	if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		ret = msh_cd(cmd);
	return (ret);
}

int	execute_builtin_by_parent(t_cmd *cmd, char **envp, int *saved_io)
{
	if ((ft_strcmp(cmd->cmd[0], "exit") == 0 \
			&& arrsize((void **)cmd->cmd) <= 2))
	{
		close(saved_io[0]);
		close(saved_io[1]);
	}
	return (execute_builtin(cmd, envp));
}
