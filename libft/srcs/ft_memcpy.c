/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoroko <dsoroko@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:21:55 by dsoroko           #+#    #+#             */
/*   Updated: 2022/04/27 18:33:29 by dsoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (n == 0 || dst == src)
		return (dst);
	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}

// #include <stdio.h>
// #include <strings.h>
// int main()
// {
// 	char dst[100] = "Here is dst";
// 	char src[100] = "Here is src";

// 	ft_memcpy(dst, src, sizeof(src));
// 	printf("dst after ft_memcpy(): %s\n", dst);
// 	memcpy(dst, src, sizeof(src));
// 	printf("dst after memcpy(): %s\n", dst);
// 	return 0;
// }