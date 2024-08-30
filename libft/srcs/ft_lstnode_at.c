/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnode_at.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:03:21 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/21 19:03:22 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnode_at(t_list *list, int index)
{
	int	i;

	i = 0;
	while (list)
	{
		if (i == index)
			return (list);
		i++;
		list = list->next;
	}
	return (NULL);
}
