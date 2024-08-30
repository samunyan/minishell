/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:15:22 by samunyan          #+#    #+#             */
/*   Updated: 2022/12/07 16:35:44 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_num_str(char	*str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

static int	arrsize(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static void	free_mem(t_cmd *cmd, char **envp)
{
	free_cmd(cmd);
	ft_free_arr((void **)envp);
	ft_lstclear(&g_envars, free_envar);
}

int	msh_exit(t_cmd *cmd, char **envp)
{
	int	exitcode;
	int	len;

	if (isatty(STDOUT_FILENO))
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		rl_clear_history();
	}
	len = arrsize((void **)cmd->cmd);
	if (len == 1)
		exitcode = EXIT_SUCCESS;
	else if (len == 2 && (is_num_str(cmd->cmd[1])))
		exitcode = ft_atoi(cmd->cmd[1]);
	else if (len == 2)
	{
		msh_error(msh_strerror, ERRNUM_EXIT_OPT, "exit");
		exitcode = 255;
	}
	else
	{
		msh_error(msh_strerror, ERRNUM_CMD_ARGS, "exit");
		return (EXIT_FAILURE);
	}
	free_mem(cmd, envp);
	exit(exitcode);
}
