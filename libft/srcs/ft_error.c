/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:50:34 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/21 15:50:36 by samunyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_err_msg(char *(*f)(int), int errnum, const char *msg)
{
	static char	buf[4096];
	char		*errstr;

	ft_memset(buf, 0, 4096);
	ft_strlcat(buf, (char *)msg, ft_strlen((char *)msg) + 1);
	errstr = f(errnum);
	if (errstr)
	{
		ft_strlcat(buf, ": ", ft_strlen(buf) + ft_strlen(": ") + 1);
		ft_strlcat(buf, errstr, ft_strlen(buf) + ft_strlen(errstr) + 1);
	}
	ft_strlcat(buf, "\n", ft_strlen(buf) + ft_strlen("\n") + 1);
	if (write(STDERR_FILENO, buf, ft_strlen(buf)) == -1)
		perror("write in err_msg");
}
