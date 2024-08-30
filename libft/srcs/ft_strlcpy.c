/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoroko <dsoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:50:20 by dsoroko           #+#    #+#             */
/*   Updated: 2022/10/24 15:18:20 by dsoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	i;

	srclen = 0;
	while (src[srclen])
		srclen++;
	if (dstsize == 0)
		return (srclen);
	i = 0;
	while (src[i] && i < (dstsize - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (srclen);
}

// #include <stdio.h>
// #include <string.h>
// int		main(void)
// {
// 	char	dest[50];
// 	char	*src;
// 	int		size;

// 	src = "hello, here is the dest";
// 	size = 6;
// 	printf("%lu\n", ft_strlcpy(dest, src, size));
// 	printf("%s\n", dest);
// 	printf("%lu\n", strlcpy(dest, src, size));
// 	printf("%s\n", dest);
// }

// Функция strlcpy копирует из строки src в буфер dst
//не более чем size - 1 символов
// и гарантированно устанавливает в конец строки нулевой символ.
// возвращает размер строки по адресу src.
