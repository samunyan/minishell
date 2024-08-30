/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:53:17 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/21 15:53:18 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strappend(char **dst, const char *src)
{
	char	*tmp;

	if (!(*dst))
		*dst = ft_strdup((char *)src);
	else
	{
		tmp = ft_strjoin(*dst, (char *)src);
		free(*dst);
		*dst = tmp;
	}
	return (*dst);
}
