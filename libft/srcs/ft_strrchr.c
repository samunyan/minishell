/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoroko <dsoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:01:39 by dsoroko           #+#    #+#             */
/*   Updated: 2022/10/24 15:17:57 by dsoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *s, int c)
{
	char	find;
	int		i;

	find = (unsigned int)c;
	i = ft_strlen(s);
	while (i > 0)
	{
		if (s[i] == find)
			return ((char *)s + i);
		i--;
	}
	if (s[i] == find)
		return ((char *)s);
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	const char str[] = "Here.is.the.string";
// 	const char ch = 'H';
// 	char *result;

// 	result = ft_strrchr(str, ch);
// 	printf("String after a character is %s\n", result);
// 	result = strrchr(str, ch);
// 	printf("String after a character is %s\n", result);
// 	return (0);
// }
