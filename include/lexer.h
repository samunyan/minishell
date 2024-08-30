/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:45:00 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/12/07 17:37:36 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*
 * FLAGS
 * operator flags
 */
# define W_GREATER			 1
# define W_GREATERGREATER	 2
# define W_LESS				 4
# define W_LESSLESS			 8
# define W_PIPE				16
/*
 * expansion flag
 */
# define W_HASDOLLAR		32
/*
 * quoting flags
 */
# define W_QUOTED			64
# define W_DQUOTED		   128
/*
 * eof flag
 */
# define W_NULL			   256
/*
 * CHAR TYPES
 * separating char types and strings
 */
# define C_GREATER			'>'
# define C_LESS				'<'
# define C_PIPE				'|'
# define C_SPACE			' '
# define C_TAB				'\t'
# define C_NULL				'\0'
/*
 * simple char types
 */
# define C_DOLLAR			'$'
# define C_QUOTE			'\''
# define C_DQUOTE			'\"'

typedef struct s_token
{
	char	*text;
	int		flag;
}	t_token;

typedef struct s_lex_dispatch
{
	char	c;
	int		(*f)(char c, int *i, size_t len, t_list **list);
}	t_lex_dispatch;
/*
 * lex_init
 */
t_token	*token_init(size_t len);
int		tok_list_init(t_list **list, size_t len);
/*
 * lex_utils
 */
void	clear_token(void *ptr);
int		add_token(size_t len, t_list **list);
void	dollar_flag(t_token *token);
/*
 * lex_null
 */
int		lex_null(char c, int *i, size_t len, t_list **list);
/*
 * lex_space
 */
int		lex_space(char c, int *i, size_t len, t_list **list);
/*
 * lex_pipe
 */
int		lex_pipe(char c, int *i, size_t len, t_list **list);
/*
 * lex_redir
 */
int		lex_dgreater(t_token *token, int *i);
int		lex_greater(char c, int *i, size_t len, t_list **list);
int		lex_dless(t_token *token, int *i);
int		lex_less(char c, int *i, size_t len, t_list **list);
/*
 * lex_quotes
 */
int		lex_squote(char c, int *i, size_t len, t_list **list);
int		lex_dquote(char c, int *i, size_t len, t_list **list);
/*
 * lex_char
 */
int		lex_char(char c, int *i, size_t len, t_list **list);
/*
 * lexer
 */
int		lex(char c, int *i, size_t len, t_list **list);
t_list	*lexer(char *input);

#endif