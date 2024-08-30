/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:46:10 by samunyan          #+#    #+#             */
/*   Updated: 2022/12/07 17:46:11 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup2_and_close_oldfd(int oldfd, int newfd)
{
	if (oldfd == newfd)
		return (1);
	if (dup2(oldfd, newfd) == -1)
	{
		msh_error(strerror, errno, "dup2");
		return (-1);
	}
	close(oldfd);
	return (1);
}

void	close_stdio(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

void	clear_cmd_list_except(t_list **cmd_list, void *content)
{
	t_list	*current;
	t_list	*next;

	current = *cmd_list;
	while (current != NULL)
	{
		next = current->next;
		if (current->content != content)
			free_cmd(current->content);
		free(current);
		current = next;
	}
	*cmd_list = NULL;
}
