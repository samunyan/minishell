/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:51:28 by samunyan          #+#    #+#             */
/*   Updated: 2022/12/07 16:33:00 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_with_newline(char **dst, char *src)
{
	char	*res;

	res = ft_strjoin(src, "\n");
	if (!res)
	{
		free(*dst);
		*dst = NULL;
		return (NULL);
	}
	ft_strappend(dst, res);
	free(res);
	return (*dst);
}

int	msh_env(char **envp)
{
	char	*output;
	size_t	i;

	i = 0;
	output = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PIPESTATUS=", ft_strlen("PIPESTATUS=")) != 0)
			if (!append_with_newline(&output, envp[i]))
				return (EXIT_FAILURE);
		i++;
	}
	if (write(STDOUT_FILENO, output, strlen(output)) == -1)
	{
		free(output);
		msh_error(strerror, errno, "write");
		return (EXIT_FAILURE);
	}
	free(output);
	return (EXIT_SUCCESS);
}
