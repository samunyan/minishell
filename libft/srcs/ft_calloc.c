/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsoroko <dsoroko@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:05:18 by dsoroko           #+#    #+#             */
/*   Updated: 2022/04/27 16:32:32 by dsoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	mem = malloc(size * count);
	if (!mem)
		return (NULL);
	ft_bzero(mem, size * count);
	return (mem);
}

// int main ()pwd
// {
// 	char *ptr;
// 	ptr = ft_calloc(5, sizeof(int));
// 	free(ptr);
// }

// Функция calloc() выделяет память, 
// размер которой равен значению выражения count * size, 
// т.е. память, достаточную для размещения массива, 
// содержащего num объектов размером size. 
// Все биты распределенной памяти инициализируются нулями.