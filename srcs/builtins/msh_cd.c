/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoroko <dsoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:24:32 by dsoroko           #+#    #+#             */
/*   Updated: 2022/12/06 17:28:49 by dsoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//TODO forgot to free new_path in cd, is this ok now?
static char	*get_env_content(t_list *list, char *name)
{
	t_list	*current;

	current = list;
	while (current)
	{
		if (ft_strcmp(name, ((t_envar *)(current->content))->name) == 0)
			return (((t_envar *)(current->content))->value);
		current = current->next;
	}
	return (NULL);
}

static void	change_pwd(char *path)
{
	t_list	*current;

	current = g_envars;
	while (current)
	{
		if (ft_strcmp("PWD", ((t_envar *)(current->content))->name) == 0)
		{
			free(((t_envar *)(current->content))->value);
			((t_envar *)(current->content))->value = path;
		}
		current = current->next;
	}
}

static int	cd_to_home(void)
{
	char	*home_path;
	char	*tmp;

	home_path = get_env_content(g_envars, "HOME");
	if (home_path == NULL)
	{
		msh_error(msh_strerror, ERRNUM_HOME, "cd");
		return (EXIT_FAILURE);
	}
	if (chdir(home_path) == -1)
	{
		msh_error(strerror, errno, home_path);
		return (EXIT_FAILURE);
	}
	if (find_envar("PWD"))
	{
		tmp = ft_strdup(home_path);
		if (!tmp)
			return (EXIT_FAILURE);
		change_pwd(tmp);
	}
	return (EXIT_SUCCESS);
}

static int	cd_to_dir(char *path)
{
	char	*new_path;

	if (chdir(path) == -1)
	{
		msh_error(strerror, errno, path);
		return (EXIT_FAILURE);
	}
	if (find_envar("PWD"))
	{
		new_path = getcwd(NULL, 0);
		if (!new_path)
		{
			msh_error(strerror, errno, "getcwd in cd_to_dir");
			return (EXIT_FAILURE);
		}
		change_pwd(new_path);
	}
	return (EXIT_SUCCESS);
}

int	msh_cd(t_cmd *cmd)
{
	if (cmd->cmd[1] == NULL)
	{
		return (cd_to_home());
	}
	else
		return (cd_to_dir(cmd->cmd[1]));
}
