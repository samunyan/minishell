/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:44:47 by samunyan          #+#    #+#             */
/*   Updated: 2022/12/07 13:51:47 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	msh_syntax_error(char *buf, char *errstr, const char *msg)
{
	ft_strlcat(buf, errstr, ft_strlen(buf) + ft_strlen(errstr) + 1);
	if (msg)
	{
		ft_strlcat(buf, " '", ft_strlen(buf) + ft_strlen(" '") + 1);
		ft_strlcat(buf, (char *)msg, \
		ft_strlen(buf) + ft_strlen((char *)msg) + 1);
		ft_strlcat(buf, "'\n", ft_strlen(buf) + ft_strlen("'\n") + 1);
	}
	else
		ft_strlcat(buf, "\n", ft_strlen(buf) + ft_strlen("\n") + 1);
	write(STDERR_FILENO, buf, ft_strlen(buf));
}

void	msh_error(char *(*f)(int), int errnum, const char *msg)
{
	static char	buf[4096];
	char		*errstr;

	ft_memset(buf, 0, 4096);
	ft_strlcat(buf, EXE, ft_strlen(EXE) + 1);
	ft_strlcat(buf, ": ", ft_strlen(buf) + ft_strlen(": ") + 1);
	if (errnum == ERRNUM_SYNTAX || errnum == ERRNUM_SYNTAX_EOF)
	{
		errstr = f(errnum);
		msh_syntax_error(buf, errstr, msg);
		return ;
	}
	ft_strlcat(buf, (char *)msg, ft_strlen(buf) + ft_strlen((char *)msg) + 1);
	errstr = f(errnum);
	if (errstr)
	{
		ft_strlcat(buf, ": ", ft_strlen(buf) + ft_strlen(": ") + 1);
		ft_strlcat(buf, errstr, ft_strlen(buf) + ft_strlen(errstr) + 1);
	}
	ft_strlcat(buf, "\n", ft_strlen(buf) + ft_strlen("\n") + 1);
	write(STDERR_FILENO, buf, ft_strlen(buf));
}

char	*msh_strerror(int def_errnum)
{
	size_t						i;
	static t_def_err_dispatch	dispatch[N_DEF_ERRORS] = {
	{ERRNUM_SYNTAX_EOF, ERRSTR_SYNTAX_EOF},
	{ERRNUM_CMD, ERRSTR_CMD},
	{ERRNUM_CMD_ARGS, ERRSTR_CMD_ARGS},
	{ERRNUM_SYNTAX, ERRSTR_SYNTAX},
	{ERRNUM_EXIT_OPT, ERRSTR_EXIT_OPT},
	{ERRNUM_HOME, ERRSTR_HOME},
	{ERRNUM_EXPORT, ERRSTR_EXPORT}};

	i = 0;
	while (i < N_DEF_ERRORS)
	{
		if (dispatch[i].def_ernnum == def_errnum)
			return (dispatch[i].def_errstr);
		i++;
	}
	return (NULL);
}
