/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoroko <dsoroko@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 19:30:26 by dsoroko           #+#    #+#             */
/*   Updated: 2022/04/27 18:33:29 by dsoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*b_ret;

	b_ret = (char *)b;
	while (len > 0)
	{
		*b_ret = c;
		b_ret++;
		len--;
	}
	return (b);
}

// #include <stdio.h>
// #include <strings.h> 
// int main()
// {
// 	char str[100] = "0123456789";
// 	char str2[100] = "0123456789";

// 	ft_memset(str, '.', 3);
// 	memset(str2, '.', 3);
// 	printf("After ft_memset(): %s\n", str);
// 	printf("After memset(): %s\n", str2);
// 	return 0;
// }

//Функция memset заполняет первые len байт области памяти, 
//на которую указывает аргумент b, 
//символом, код которого указывается аргументом c.