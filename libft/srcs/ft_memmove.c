/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoroko <dsoroko@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:33:00 by dsoroko           #+#    #+#             */
/*   Updated: 2022/04/27 18:33:29 by dsoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*my_dest;
	unsigned char	*my_src;

	my_dest = (unsigned char *)(dst);
	my_src = (unsigned char *)(src);
	i = 0;
	if (!my_dest && !my_src)
		return (0);
	if (my_dest > my_src)
	{
		while (len > 0)
		{
			my_dest[len - 1] = my_src[len - 1];
			len--;
		}
	}
	while (i < len)
	{
		my_dest[i] = my_src[i];
		i++;
	}
	return (my_dest);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	char dst[100] = "Hello";
// 	char src[100] = "here is the string";
// 	ft_memmove(dst, src + 3, 3);
// 	ft_memmove(dst, dst + 3, 3);
// 	printf("dst after ft_memmove: |%s|\n", dst);
// 	memmove(dst, src + 3, 3);
// 	printf("dst after memmove: |%s|\n", dst);
// 	return 0;
// }
