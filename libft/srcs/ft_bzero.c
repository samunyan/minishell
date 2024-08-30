/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoroko <dsoroko@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:52:13 by dsoroko           #+#    #+#             */
/*   Updated: 2022/04/27 18:33:29 by dsoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

// #include <stdio.h>
// #include <strings.h>
// int main()
// {
// 	char str[100] = "0123456789";
// 	char str2[100] = "0123456789";

// 	ft_bzero(str + 3, 1);
// 	bzero(str2 + 3, 1);
// 	printf("After ft_memset(): %s\n", str);
// 	printf("After memset(): %s\n", str) 2;
// 	return 0;
// }

// Функция memset заполняет первые len байт области памяти,
// на которую указывает аргумент b, 
// символом, код которого указывается аргументом c.
