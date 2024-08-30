/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:02:57 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/12/07 17:07:58 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_double_quoted(const char *s)
{
	return (*s == '"' && s[ft_strlen((char *)s) - 1] == '"');
}

char	*get_delim_without_quotes(char *delim)
{
	char	*new_delim;

	new_delim = ft_strdup(delim + 1);
	if (new_delim)
		new_delim[ft_strlen(new_delim) - 1] = '\0';
	return (new_delim);
}
