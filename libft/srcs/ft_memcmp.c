/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoroko <dsoroko@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:18:02 by dsoroko           #+#    #+#             */
/*   Updated: 2022/04/27 18:33:29 by dsoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	const void *s1 = "Hello";
// 	const void *s2 = "HellO";
// 	int ret = memcmp(s1, s2, 5);
// 	int ret2 = ft_memcmp(s1, s2, 5);
// 	printf("%d\n", ret);
// 	printf("%d\n", ret2);
// }

// Функция memcmp побайтно сравнивает два массива (области памяти), 
// на которые указывают аргументы s1 и s2.
// Каждый байт массива определяется типом unsigned char.
// Сравнение продолжается, 
// пока не будут проверено n байт или пока не встретятся отличающиеся байты.
