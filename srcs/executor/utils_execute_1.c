/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <gscarama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:16:36 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/24 13:56:47 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_right_path(char **paths, char *cmd, char **bin_path)
{
	size_t	i;

	i = 0;
	while (paths[i])
	{
		*bin_path = ft_strjoin(paths[i], "/");
		if (!*bin_path)
			return (0);
		ft_strappend(bin_path, cmd);
		if (!*bin_path)
			return (0);
		if (access(*bin_path, F_OK) == 0)
			break ;
		free(*bin_path);
		*bin_path = NULL;
		i++;
	}
	return (1);
}

int	get_bin_path_for_cmd(char *cmd, char **bin_path)
{
	char	**paths;
	int		ret;

	if (ft_strchr(cmd, '/'))
	{
		*bin_path = ft_strdup(cmd);
		return (*bin_path != NULL);
	}
	paths = get_bin_paths();
	if (!paths)
	{
		*bin_path = ft_strdup(cmd);
		return (*bin_path != NULL);
	}
	ret = find_right_path(paths, cmd, bin_path);
	ft_free_arr((void **)paths);
	return (ret);
}

char	**get_bin_paths(void)
{
	char	**paths;
	char	*value;

	value = msh_getenv("PATH");
	if (!value)
		return (NULL);
	paths = ft_split(value, ':');
	return (paths);
}

void	close_pipes(int **pipes_fd)
{
	int	i;

	i = 0;
	while (pipes_fd[i])
	{
		close(pipes_fd[i][READ]);
		close(pipes_fd[i][WRITE]);
		i++;
	}
}

int	**create_pipes(int n_cmds)
{
	int	**pipes_fd;
	int	i;

	pipes_fd = ft_malloc(sizeof(int *) * (n_cmds));
	if (!(pipes_fd))
		return (NULL);
	i = 0;
	while (i < n_cmds - 1)
	{
		pipes_fd[i] = malloc(sizeof(int) * 2);
		{
			if (!pipes_fd[i] || pipe(pipes_fd[i]) < 0)
			{
				pipes_fd[i] = NULL;
				close_pipes(pipes_fd);
				ft_free_arr((void **)pipes_fd);
				return (NULL);
			}
		}
		i++;
	}
	return (pipes_fd);
}
