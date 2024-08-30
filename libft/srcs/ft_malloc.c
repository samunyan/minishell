/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:50:21 by samunyan          #+#    #+#             */
/*   Updated: 2022/12/07 17:18:19 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t size)
{
	void	*p;

	p = malloc(size);
	if (p)
		ft_memset(p, 0, size);
	else
		ft_err_msg(strerror, errno, "ft_malloc");
	return (p);
}
