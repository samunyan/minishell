/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:10:11 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/30 12:10:12 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_bin(const char *bin_path)
{
	struct stat	path_stat;

	ft_memset(&path_stat, 0, sizeof(struct stat));
	stat(bin_path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

static int	bin_path_is_not_valid(char *bin_path, t_cmd *cmd)
{
	if (!bin_path || !is_bin(bin_path))
	{
		if (bin_path && access(bin_path, F_OK) != 0)
			msh_error(strerror, ENOENT, cmd->cmd[0]);
		else
			msh_error(msh_strerror, ERRNUM_CMD, cmd->cmd[0]);
		return (127);
	}
	if (access(bin_path, X_OK) != 0)
	{
		msh_error(strerror, errno, cmd->cmd[0]);
		return (126);
	}
	return (0);
}

int	execute_simple_command(t_cmd *cmd, char **envp)
{
	char	*bin_path;
	int		error;

	signal(SIGQUIT, SIG_DFL);
	if (!cmd->cmd[0] || !*(cmd->cmd[0]))
		return (EXIT_SUCCESS);
	if (is_builtin(cmd))
		return (execute_builtin(cmd, envp));
	bin_path = NULL;
	if (!get_bin_path_for_cmd(cmd->cmd[0], &bin_path))
		return (EXIT_FAILURE);
	error = bin_path_is_not_valid(bin_path, cmd);
	if (error)
	{
		free(bin_path);
		return (error);
	}
	execve(bin_path, cmd->cmd, envp);
	msh_error(strerror, errno, "execve in execute_simple_command");
	free(bin_path);
	return (EXIT_FAILURE);
}
