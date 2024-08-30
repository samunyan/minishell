/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <gscarama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:35:19 by gscarama          #+#    #+#             */
/*   Updated: 2022/12/07 16:12:08 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_squote(char **arg)
{
	int		first;
	size_t	last;
	char	*nstr;

	first = 0;
	last = ft_strlen(*arg) - 1;
	if (((*arg)[first] == '\'' && (*arg)[last] == '\'')
		|| ((*arg)[first] == '\"' && (*arg)[last] == '\"'
			&& locate_dollar(*arg) < 0))
	{
		nstr = ft_strdup(&(*arg)[first + 1]);
		nstr[last - 1] = '\0';
		free(*arg);
		*arg = nstr;
		return (true);
	}
	return (false);
}

char	*replace_noenv(char *text)
{
	t_row	row;
	char	*res;

	res = (char *)malloc(sizeof(char) * (ft_strlen(text) + 2));
	if (res == NULL)
		return (NULL);
	row.i = 0;
	row.j = 0;
	replace_quotes(res, text, &row);
	row.j++;
	while (ft_isalnum(text[row.j + row.i]))
		row.j++;
	copy_final(res, text, &row);
	res[row.i] = '\0';
	return (res);
}

char	*replace_qst(char *text, char *param, int exitcode)
{
	char	*res;
	char	*excode;
	size_t	param_len;
	t_row	row;

	res = (char *)malloc(sizeof(char) * (ft_strlen(text) + 5));
	if (res == NULL)
		return (NULL);
	row.i = 0;
	row.j = 0;
	param_len = ft_strlen(param) + 1;
	replace_quotes(res, text, &row);
	row.k = 0;
	excode = ft_itoa(exitcode);
	while (excode[row.k])
	{
		res[row.i + row.k] = excode[row.k];
		row.k++;
	}
	free(excode);
	copy_final(&res[row.k], &text[param_len], &row);
	res[row.i + row.k] = '\0';
	return (res);
}
