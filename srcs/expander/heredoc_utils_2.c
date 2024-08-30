/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <gscarama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:35:19 by gscarama          #+#    #+#             */
/*   Updated: 2022/12/08 13:43:49 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*found_env(char **text, t_list *env, char *param)
{
	char	*res;

	res = replace_env(*text, param, ((t_envar *)env->content)->value);
	if (res == NULL)
		return (NULL);
	free(*text);
	*text = res;
	return (res);
}

char	*no_env(char **text)
{
	char	*res;

	res = replace_noenv(*text);
	if (res == NULL)
		return (NULL);
	free(*text);
	*text = res;
	return (res);
}

char	*found_qst(char **text, char *param, int exitcode)
{
	char	*res;

	res = replace_qst(*text, param, exitcode);
	if (res == NULL)
		return (NULL);
	free(*text);
	*text = res;
	return (res);
}

char	*go_through_envs(char **text, t_list *env, char *param)
{
	char	*res;
	t_list	*envp;

	res = NULL;
	envp = env;
	while (envp)
	{
		if (ft_strncmp(((t_envar *)envp->content)->name, param,
				ft_strlen(param) + 1) == 0)
		{
			res = found_env(text, envp, param);
			break ;
		}
		else if (ft_strncmp(param, "?", ft_strlen(param) + 1) == 0
			|| ft_strncmp(param, "PIPESTATUS", ft_strlen(param) + 1) == 0)
		{
			res = found_qst(text, param, get_exitcode());
			break ;
		}
		envp = envp->next;
	}
	if (!res)
		res = no_env(text);
	return (res);
}

int	expd(char **text, t_list *env, char *param)
{
	if (go_through_envs(text, env, param) == NULL)
		return (-1);
	return (1);
}
