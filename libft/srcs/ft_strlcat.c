/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoroko <dsoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 09:05:22 by dsoroko           #+#    #+#             */
/*   Updated: 2022/10/24 15:18:25 by dsoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	destlen;
	size_t	srclen;

	i = 0;
	destlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstsize <= destlen)
		return (dstsize + srclen);
	while (src[i] && destlen + i + 1 < dstsize)
	{
		dst[destlen + i] = src[i];
		i++;
	}
	dst[destlen + i] = 0;
	return (destlen + srclen);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	char s1[50] = "String1";
// 	char s2[50] = "String2";
// 	size_t dest;
// 	size_t dest2;

// 	dest = ft_strlcat(s1, s2, 15);
// 	dest2 = strlcat(s1, s2, 15);
// 	printf("Final string : %s\n", s1);
// 	printf("dest after ft_strlcat : %zu\n", dest);
// 	printf("dest after strlcat : %zu\n", dest2);
// 	return (0);
// }