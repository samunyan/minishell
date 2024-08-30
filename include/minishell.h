/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:38:11 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/12/07 17:41:08 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# include "lexer.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "error.h"
# include "envars.h"
# include "expander.h"
# include "execute.h"
# include "signals.h"
# include "builtins.h"
# include "parser.h"
# define PS1	"msh > "
# define PS2	"> "
# define EXE	"msh"

# define HEREDOC 		2
# define INFILE 		3
# define CREATE_OUTFILE 4
# define APPEND_OUTFILE 5
# define REDIR_IN 		6
# define REDIR_OUT 		7

typedef struct s_redir
{
	int		type_redir;
	int		type_in;
	char	*in;
	char	*heredoc_delim;
	int		type_out;
	char	*out;
}	t_redir;

typedef struct s_cmd
{
	char	**cmd;
	t_list	*redirections;
	int		pid;
	int		i_child;
}	t_cmd;

t_cmd	*get_t_cmd(t_list *list);
void	free_cmd(void *cmd);
void	clear_redir(void *redir);
t_token	*get_t_token(t_list *node);

#endif