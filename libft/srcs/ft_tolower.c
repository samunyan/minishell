/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoroko <dsoroko@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:44:12 by dsoroko           #+#    #+#             */
/*   Updated: 2022/04/27 18:33:29 by dsoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}

// #include <stdio.h>
// int main()
// {
// 	char c, result;

// 	c = 'M';
// 	result = ft_tolower(c);
// 	printf("The result is %c\n", result);
// 	c = 'g';
// 	result = ft_tolower(c);
// 	printf("The result is %c\n", result);

// 	c = '+';
// 	result = ft_tolower(c);
// 	printf("The result is %c\n", result);

// 	return 0;
// }
