/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:39:13 by samunyan          #+#    #+#             */
/*   Updated: 2022/12/07 17:33:59 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>

# define N_DEF_ERRORS			7
# define ERRNUM_SYNTAX_EOF		1
# define ERRSTR_SYNTAX_EOF		"syntax error: unexpected end of file"
# define ERRNUM_CMD				2
# define ERRSTR_CMD				"command not found"
# define ERRNUM_CMD_ARGS		3
# define ERRSTR_CMD_ARGS		"too many arguments"
# define ERRNUM_SYNTAX			4
# define ERRSTR_SYNTAX			"syntax error near unexpected token"
# define ERRNUM_EXIT_OPT		5
# define ERRSTR_EXIT_OPT		"numeric argument required"
# define ERRNUM_HOME			6
# define ERRSTR_HOME			"HOME not set"
# define ERRNUM_EXPORT			7
# define ERRSTR_EXPORT			"not a valid identifier"

typedef struct s_def_err_dispatch
{
	int			def_ernnum;
	char		*def_errstr;
}				t_def_err_dispatch;

void	msh_error(char *(*f)(int), int errnum, const char *msg);
char	*msh_strerror(int def_errnum);

#endif