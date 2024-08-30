/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoroko <dsoroko@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:33:36 by dsoroko           #+#    #+#             */
/*   Updated: 2022/04/27 18:33:29 by dsoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}

// void ft_f(unsigned int i, char *c)
// {
//     if ((*c >= 'A' && *c <= 'Y') || (*c >= 'a' && *c <= 'y'))
//         *c += 1;
//     if (*c == 'Z' || *c == 'z')
//         *c += ('A' - 'Z');
// }

// #include <stdio.h>
// int main()
// {
// 	char str[] = "Here is the string";
// 	ft_striteri(str, &ft_f);
// 	printf("%s\n", str);
// }
