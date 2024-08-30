/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_simple_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:54:15 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/30 17:54:17 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(t_cmd *cmd, char **envp)
{
	int	error;

	error = execute_simple_command(cmd, envp);
	free_cmd(cmd);
	ft_free_arr((void **)envp);
	ft_lstclear(&g_envars, free_envar);
	close_stdio();
	exit(error);
}

static int	parent(pid_t pid)
{
	int		wstatus;
	int		error;

	if (pid < 0)
	{
		msh_error(strerror, errno, "fork in parent");
		return (EXIT_FAILURE);
	}
	signal(SIGINT, SIG_IGN);
	wait(&wstatus);
	signal(SIGINT, handle_sigint);
	error = get_exitcode_from_child(wstatus);
	return (error);
}

static int	execute_command_with_fork(t_cmd *cmd, char **envp, int *saved_io)
{
	pid_t	pid;
	int		error;

	pid = fork();
	if (!pid)
	{
		close(saved_io[0]);
		close(saved_io[1]);
		child(cmd, envp);
	}
	error = parent(pid);
	return (error);
}

static int	restore_io(int *saved_io)
{
	if (dup2_and_close_oldfd(saved_io[0], STDIN_FILENO) == -1
		|| dup2_and_close_oldfd(saved_io[1], STDOUT_FILENO) == -1)
		return (1);
	return (0);
}

void	do_simple_command(t_list *cmd_list, char **envp)
{
	int		error;
	int		error2;
	int		saved_io[2];
	t_cmd	*cmd;

	cmd = get_t_cmd(cmd_list);
	clear_cmd_list_except(&cmd_list, cmd);
	error = set_io_simple_command(cmd, saved_io);
	if (error)
	{
		free_cmd(cmd);
		update_exitcode(EXIT_FAILURE);
		return ;
	}
	if (cmd->cmd[0] && is_builtin(cmd))
		error = execute_builtin_by_parent(cmd, envp, saved_io);
	else
		error = execute_command_with_fork(cmd, envp, saved_io);
	error2 = restore_io(saved_io);
	free_cmd(cmd);
	if (error2)
		error = error2;
	update_exitcode(error);
}
