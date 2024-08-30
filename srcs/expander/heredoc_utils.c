/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <gscarama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:35:19 by gscarama          #+#    #+#             */
/*   Updated: 2022/12/08 14:10:17 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	locate_dollar(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (-2);
	while (arg[i])
	{
		if (arg[i] == '$')
			return (i);
		i++;
	}
	return (-2);
}

char	*dollar_str(char *args)
{
	char	*res;
	t_row	row;

	row.i = locate_dollar(args) + 1;
	if (row.i != -1)
	{
		row.j = row.i;
		while (ft_isalnum(args[row.j]) || args[row.j] == '?'
			|| args[row.j] == '_')
			row.j++;
		res = (char *)ft_malloc((row.j - row.i) + 1);
		if (!res)
			return (NULL);
		row.k = 0;
		while ((args[row.i + row.k] && args[row.i + row.k] != '\"'
				&& args[row.i + row.k] != '$'
				&& ft_isalnum(args[row.i + row.k]))
			|| args[row.i + row.k] == '?' || args[row.i + row.k] == '_')
		{
			res[row.k] = args[row.i + row.k];
			row.k++;
		}
		return (res);
	}
	return (NULL);
}

void	replace_quotes(char *res, char *word, t_row *row)
{
	while (word[row->i + row->j] && word[row->i + row->j] != '$'
		&& word[row->i + row->j] != '\"')
	{
		res[row->i] = word[row->i + row->j];
		row->i++;
	}
	if (word[row->i + row->j] == '\"')
		row->j++;
	while (word[row->i + row->j] && word[row->i + row->j] != '$'
		&& word[row->i + row->j] != '\"')
	{
		res[row->i] = word[row->i + row->j];
		row->i++;
	}
	if (word[row->i + row->j] == '\"')
		row->j++;
}

void	copy_final(char *res, char *word, t_row *row)
{
	if (word[row->i + row->j] == '$')
	{
		res[row->i] = '$';
		row->i++;
	}
	while (word[row->i + row->j] && word[row->i + row->j] != '$'
		&& word[row->i + row->j] != '\"')
	{
		res[row->i] = word[row->i + row->j];
		row->i++;
	}
	if (word[row->i + row->j] == '\"')
		row->j++;
	while (word[row->i + row->j])
	{
		res[row->i] = word[row->i + row->j];
		row->i++;
	}
}

char	*replace_env(char *word, char *param, char *env)
{
	char	*res;
	t_row	row;
	size_t	param_len;

	row.i = 0;
	row.j = 0;
	param_len = ft_strlen(param) + 1;
	res = ft_malloc(ft_strlen(word) + ft_strlen(env) + 1);
	if (!res)
		return (NULL);
	replace_quotes(res, word, &row);
	ft_strcpy(&res[row.i], env);
	row.k = ft_strlen(env);
	copy_final(&res[row.k], &word[param_len], &row);
	return (res);
}
