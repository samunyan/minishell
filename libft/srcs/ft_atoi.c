/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoroko <dsoroko@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:22:07 by dsoroko           #+#    #+#             */
/*   Updated: 2022/04/27 18:33:29 by dsoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	atoi_limits(unsigned long long result, int sign, int size)
{
	unsigned long long	max;

	max = 9223372036854775807U;
	if (((result > max) || size > 19) && sign > 0)
		return (-1);
	else if (((result > (max + 1)) || size > 19) && sign < 0)
		return (0);
	return (result * sign);
}

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	int					i;
	int					sign;
	int					size;

	result = 0;
	i = 0;
	sign = 1;
	size = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
		size ++;
	}
	return (atoi_limits(result, sign, size));
}

// #include <stdlib.h>
// #include <stdio.h>
// int main()
// {
// 	printf("%d ", ft_atoi("18446744073709551615"));
// 	printf("\n");
// 	printf("%d ", atoi("18446744073709551615"));
// 	printf("\n");
// 	printf("%d ", ft_atoi("-9223372036854775807"));
// 	printf("\n");
// 	printf("%d ", atoi("-9223372036854775807"));
// 	printf("\n");
// 	printf("%d ", ft_atoi(" ---+--+1234ab567"));
// 	printf("\n");
// 	printf("%d ", atoi(" ---+--+1234ab567"));
// 	printf("\n");
// 	printf("%d ", ft_atoi("-9223372036854775808"));
// 	printf("\n");
// 	printf("%d ", atoi("-9223372036854775808"));
// 	printf("\n");
// 	printf("%d ", ft_atoi("9223372036854775807"));
// 	printf("\n");
// 	printf("%d ", atoi("9223372036854775807"));
// 	printf("\n");
// 	printf("%d ", ft_atoi("19489384723948723948"));
// 	printf("\n");
// 	printf("%d ", atoi("19489384723948723948"));
// }
