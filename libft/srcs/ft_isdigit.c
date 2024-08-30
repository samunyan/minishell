/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoroko <dsoroko@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:53:55 by dsoroko           #+#    #+#             */
/*   Updated: 2022/04/27 18:33:29 by dsoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (!0);
	return (0);
}

// #include <stdio.h>
// #include <ctype.h>
// int main()
// {
// 	char c, result;

// 	c = '*';
// 	result = ft_isdigit(c);
// 	printf("The result is %d\n", result);
// 	result = isdigit(c);
// 	printf("The result is %d\n", result);

// 	c = '5';
// 	result = ft_isdigit(c);
// 	printf("The result is %d\n", result);
// 	result = isdigit(c);
// 	printf("The result is %d\n", result);

// 	return 0;
// }