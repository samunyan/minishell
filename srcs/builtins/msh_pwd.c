/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:23:48 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/12/07 16:37:53 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_pwd(void)
{
	char	*ret;

	ret = NULL;
	ret = getcwd(NULL, 0);
	if (!ret)
	{
		msh_error(strerror, errno, "msh_pwd");
		return (EXIT_FAILURE);
	}
	else
	{
		write(1, ret, ft_strlen(ret));
		write(1, "\n", 1);
		free(ret);
	}
	return (EXIT_SUCCESS);
}
