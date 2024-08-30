/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:10:26 by samunyan          #+#    #+#             */
/*   Updated: 2022/12/01 12:10:27 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	supervise(int **pipes_fd, t_list *cmd_list)
{
	int			wstatus;
	int			pid;
	t_list		*tmp;

	close_pipes(pipes_fd);
	ft_free_arr((void **)pipes_fd);
	tmp = cmd_list;
	while (cmd_list)
	{
		pid = get_t_cmd(cmd_list)->pid;
		if (pid < 0)
		{
			update_exitcode(EXIT_FAILURE);
			break ;
		}
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &wstatus, 0);
		signal(SIGINT, handle_sigint);
		update_exitcode(get_exitcode_from_child(wstatus));
		cmd_list = cmd_list->next;
	}
	ft_lstclear(&tmp, free_cmd);
}

static void	execute_pipeline(t_list *cmd_list, char **envp, int **pipes)
{
	int		i_child;
	pid_t	pid;
	t_cmd	*cmd;

	i_child = 0;
	while (i_child < ft_lstsize(cmd_list))
	{
		pid = fork();
		if (pid)
		{
			get_t_cmd(ft_lstnode_at(cmd_list, i_child))->pid = pid;
			if (pid < 0)
				break ;
			i_child++;
		}
		else
		{
			cmd = get_t_cmd(ft_lstnode_at(cmd_list, i_child));
			cmd->i_child = i_child;
			clear_cmd_list_except(&cmd_list, cmd);
			do_piped_command(cmd, envp, pipes);
		}
	}
	supervise(pipes, cmd_list);
}

void	do_pipeline(t_list *cmd_list, char **envp)
{
	int		**pipes;

	pipes = create_pipes(ft_lstsize(cmd_list));
	if (!pipes)
	{
		update_exitcode(EXIT_FAILURE);
		return ;
	}
	execute_pipeline(cmd_list, envp, pipes);
}
