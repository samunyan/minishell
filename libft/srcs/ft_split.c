/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoroko <dsoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:28:12 by dsoroko           #+#    #+#             */
/*   Updated: 2022/10/24 15:18:47 by dsoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	**ft_free(int index, char **split)
{
	while (--index)
		free(split[index]);
	free(split);
	return (NULL);
}

static char	*find_next_word(char *s, char c, int index)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (index)
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			index--;
		while (index && s[i] && s[i] != c)
			i++;
	}
	j = i;
	while (s[j] && s[j] != c)
	{
		count++;
		j++;
	}
	return (ft_substr(&s[i], 0, count));
}

char	**ft_split(char *s, char c)
{
	char	**str;
	int		i;

	i = -1;
	if (!s)
		return (NULL);
	str = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!str)
		return (NULL);
	while (++i < count_words(s, c))
	{
		str[i] = find_next_word((char *)s, c, i + 1);
		if (!str[i])
			return (ft_free(i, str));
	}
	str[i] = 0;
	return (str);
}

// #include <stdio.h>
// int main()
// {
// 	char str[20] = "/Here/is/the/string";
// 	char **result = ft_split(str, '/');
// 	printf("The result is : %s\n", result[0]);
// 	printf("The result is : %s\n", result[1]);
// 	printf("The result is : %s\n", result[2]);
// 	printf("The result is : %s\n", result[3]);
// 	printf("The result is : %s\n", result[4]);
// 	return 0;
// }