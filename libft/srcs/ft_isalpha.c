/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoroko <dsoroko@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:51:25 by dsoroko           #+#    #+#             */
/*   Updated: 2022/04/27 18:33:29 by dsoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (!0);
	return (0);
}

// #include <stdio.h>
// #include <ctype.h>
// int main()
// {
// 	char c, result;

// 	c = '*';
// 	result = ft_isalpha(c);
// 	printf("The result is %d\n", result);
// 	result = isalpha(c);
// 	printf("The result is %d\n", result);

// 	c = 'g';
// 	result = ft_isalpha(c);
// 	printf("The result is %d\n", result);
// 	result = isalpha(c);
// 	printf("The result is %d\n", result);

// 	return 0;
// }
