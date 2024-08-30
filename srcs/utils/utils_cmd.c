/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <gscarama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:59:04 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/24 13:57:14 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*get_t_cmd(t_list *list)
{
	return ((t_cmd *)list->content);
}

void	clear_redir(void *redir)
{
	t_redir	*cast;

	cast = (t_redir *)redir;
	free(cast->in);
	free(cast->heredoc_delim);
	free(cast->out);
	free(cast);
	cast = NULL;
}

void	free_cmd(void *cmd)
{
	t_cmd	*cast;

	cast = cmd;
	ft_free_arr((void **)cast->cmd);
	ft_lstclear(&(cast->redirections), clear_redir);
	free(cmd);
	cmd = NULL;
}
