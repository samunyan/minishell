/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoroko <dsoroko@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:57:51 by dsoroko           #+#    #+#             */
/*   Updated: 2022/04/27 18:33:29 by dsoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
		return (!0);
	return (0);
}

// #include <stdio.h>
// #include <ctype.h>
// int main()
// {
// 	char c, result;
// 	c = '*';
// 	result = ft_isalnum(c);
// 	printf("The result is %d\n", result);
// 	result = isalnum(c);
// 	printf("The result is %d\n", result);

// 	c = 'g';
// 	result = ft_isalnum(c);
// 	printf("The result is %d\n", result);
// 	result = isalnum(c);
// 	printf("The result is %d\n", result);

// 	return 0;
// }
