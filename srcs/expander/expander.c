/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exapander.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <gscarama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:35:19 by gscarama          #+#    #+#             */
/*   Updated: 2022/12/02 15:07:42 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*go_through_all_envs(t_list *env, char *param, char *word)
{
	char	*res;
	t_list	*envp;

	res = NULL;
	envp = env;
	while (envp)
	{
		if (ft_strncmp(((t_envar *)envp->content)->name,
				param, ft_strlen(param) + 1) == 0)
		{
			res = replace_env(word, param, ((t_envar *)envp->content)->value);
			break ;
		}
		else if (ft_strncmp(param, "?", ft_strlen(param) + 1) == 0
			|| ft_strncmp(param, "PIPESTATUS", ft_strlen(param) + 1) == 0)
		{
			res = replace_qst(word, param, get_exitcode());
			break ;
		}
		envp = envp->next;
	}
	if (!res)
		res = replace_noenv(word);
	return (res);
}

char	*expand_quote(t_list *env, char *word, char *param)
{
	char	*res;

	res = go_through_all_envs(env, param, word);
	if (res == NULL)
		return (NULL);
	free (word);
	word = res;
	return (res);
}

static int	go_through_word(char **args, t_list *env)
{
	int		row;
	char	*word;
	char	*param;

	row = 0;
	while (args[row] != NULL)
	{
		while (is_squote(&args[row]) != true
			&& locate_dollar(args[row]) != -2)
		{
			word = args[row];
			param = dollar_str(args[row]);
			if (param == NULL)
				return (-1);
			args[row] = expand_quote(env, word, param);
			if (args[row] == NULL)
				return (-1);
			free(param);
		}
		row++;
	}
	return (1);
}

int	go_through_heredocs(t_list *redirections)
{
	t_redir	*redir;
	t_list	*tmp;

	tmp = redirections;
	while (tmp)
	{
		redir = (t_redir *)(tmp)->content;
		if (redir->type_redir == REDIR_IN && redir->type_in == HEREDOC)
		{
			if (expand_heredoc(&(redir->in), g_envars) == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	expander(t_list *cmd_list, t_list *env)
{
	char	**args;
	t_list	*args_head;

	args_head = cmd_list;
	while (args_head != NULL)
	{
		args = (char **)((t_cmd *)args_head->content)->cmd;
		if (go_through_word(args, env) == -1)
			return (-1);
		if (go_through_heredocs(get_t_cmd(args_head)->redirections) == -1)
			return (-1);
		args_head = args_head->next;
	}
	return (1);
}
