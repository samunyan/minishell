/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smunyans <smunyans@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 09:06:45 by smunyans          #+#    #+#             */
/*   Updated: 2022/01/24 09:06:45 by smunyans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

typedef struct s_row
{
	int	i;
	int	j;
	int	k;
}				t_row;

typedef struct s_exp
{
	int	i;
	int	ret_val;
}				t_exp;

int		expander(t_list *cmd_list, t_list *env);
int		expand_heredoc(char **text, t_list *env);
int		locate_dollar(char *arg);
char	*dollar_str(char *args);
bool	is_squote(char **arg);
char	*replace_env(char *word, char *param, char *env);
void	copy_final(char *res, char *word, t_row *row);
void	replace_quotes(char *res, char *word, t_row *row);
char	*replace_noenv(char *text);
char	*replace_qst(char *text, char *param, int exitcode);
char	*found_env(char **text, t_list *env, char *param);
char	*no_env(char **text);
char	*found_env(char **text, t_list *env, char *param);
char	*go_through_envs(char **text, t_list *env, char *param);
int		expd(char **text, t_list *env, char *param);

#endif