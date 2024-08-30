/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoroko <dsoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:08:41 by dsoroko           #+#    #+#             */
/*   Updated: 2022/10/24 15:17:34 by dsoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	j;
	size_t	str_len;

	if (!s)
		return (NULL);
	if (len >= ft_strlen(s))
		str_len = ft_strlen(s);
	else
		str_len = len;
	substr = ft_malloc(sizeof(char) * (str_len + 1));
	if (!substr)
		return (NULL);
	i = ((size_t)start);
	j = 0;
	while (i < ft_strlen(s) && j < len)
	{
		substr[j] = s[i];
		i++;
		j++;
	}
	substr[j] = '\0';
	return (substr);
}

// #include <stdio.h>
// int main()
// {
// 	char str[20] = "This is string";
// 	char *result = ft_substr(str, 0, 18);
// 	printf("The  result is: |%s|\n", result);
// 	return 0;
// }
