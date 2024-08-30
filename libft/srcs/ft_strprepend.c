/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strprepend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:27:12 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/11/30 16:11:58 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strprepend(char **dst, const char *src)
{
	char	*tmp;

	if (!(*dst))
		*dst = ft_strdup((char *)src);
	else
	{
		tmp = ft_strjoin((char *)src, *dst);
		free(*dst);
		*dst = tmp;
	}
	return (*dst);
}
