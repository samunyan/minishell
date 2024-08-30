/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoroko <dsoroko@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:03:25 by dsoroko           #+#    #+#             */
/*   Updated: 2022/04/27 18:33:29 by dsoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s2;

	s2 = (unsigned char *)s;
	while (n--)
	{
		if (*s2 == (unsigned char)c)
			return ((void *)s2);
		s2++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	const char str[] = "Here.is.String";
// 	const char ch = '.';
// 	const char ch2 = '/';
// 	char *result;

// 	result = ft_memchr(str, ch, 15);
// 	printf("String after ft_memchr is: |%s|\n", result);
// 	result = memchr(str, ch, 15);
// 	printf("String after memchr is: |%s|\n", result);
// 	result = ft_memchr(str, ch2, 15);
// 	printf("String after ft_memchr is: |%s|\n", result);
// 	result = memchr(str, ch2, 15);
// 	printf("String after memchr is: |%s|\n", result);
// 	return (0);
// }
