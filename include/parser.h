/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:37:21 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/12/07 17:41:30 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_pars_data
{
	t_list	*cmd_list;
	t_list	*current_tok;
	t_cmd	*cmd;
	int		i;
}	t_pars_data;

typedef struct s_check
{
	int	redir;
	int	heredoc;
	int	pipe;
	int	arg;
}	t_check;

/*
 * parse_init
 */
t_list		*redir_init(void);
t_cmd		*cmd_init(t_list **tok_list);
t_list		*init_cmd_list(t_list **tok_list);
t_pars_data	*init_data(t_list **tok_list);
/*
 * parse_utils
 */
void		clear_cmd(void *ptr);
/*
 * parse_arg
 */
int			parse_arg(t_list **tok_list, t_pars_data *data);
/*
 * parse_pipe
 */
int			parse_pipe(t_list **tok_list, t_pars_data *data);
/*
 * parse_redir
 */
int			word_is_operator(t_token *token);
int			parse_output(t_list **tok_list, t_pars_data *data);
int			parse_append(t_list **tok_list, t_pars_data *data);
int			parse_redir(t_list **tok_list, t_pars_data *data);
/*
 * parse_input
 */
int			parse_input(t_list **tok_list, t_pars_data *data);
/*
 * parse_heredoc
 */
int			parse_heredoc(t_list **tok_list, t_pars_data *data);
int			gather_heredoc(t_list **tok_list, t_pars_data *data);
char		*heredoc_to_string(int fd, int *error);
int			get_input_for_heredoc(t_redir *redir, char *delim);
int			is_double_quoted(const char *s);
char		*get_delim_without_quotes(char *delim);
/*
 * parse_output
 */
int			create_redir(t_pars_data *data);
int			fill_redir_out(int type_out, t_token *token, t_list *redirection);
int			parse_output(t_list **tok_list, t_pars_data *data);
/*
 * parse_append
 */
int			parse_append(t_list **tok_list, t_pars_data *data);
/*
 * parser
 */
int			word_is_redir(t_pars_data *data);
t_list		*parser(t_list **tok_list);
int			append_cmd(t_list **cmd_list);

#endif