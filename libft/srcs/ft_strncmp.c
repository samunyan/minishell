/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoroko <dsoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:02:36 by dsoroko           #+#    #+#             */
/*   Updated: 2022/10/24 15:23:02 by dsoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n > 0)
	{
		while ((s1[i] || s2[i]) && (s1[i] == s2[i]) && i < n - 1)
			i++;
		return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	char str1[15] = "ABCdef";
// 	char str2[15] = "ABCDEF";
// 	int result;

// 	result = ft_strncmp(str1, str2, 6);
// 	printf("Value returned by ft_strncmp() is: %d\n", result);

// 	result = strncmp(str1, str2, 6);
// 	printf("Value returned by strncmp() is: %d\n", result);
// 	return (0);
// }
