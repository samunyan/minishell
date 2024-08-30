/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:31:52 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/12/07 17:31:56 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include	"minishell.h"

int		msh_env(char **envp);
int		msh_exit(t_cmd *cmd, char **envp);
int		msh_echo(t_cmd *cmd);
int		msh_cd(t_cmd *cmd);
//msh_export_noarg
int		size_list(t_list *list);
int		find_min_env(t_list *envars, char **sorted, int i);
void	clear_sorted(char **sorted, int len);
//msh_export_arg
t_list	*add_envar_export(t_list **list, char *name_equal_value);
//msh_export
int		msh_export(t_cmd *cmd);
//msh_unset
void	clear_node_envar(void *content);
int		msh_unset(t_cmd *cmd);
//msh_pwd
int		msh_pwd(void);

#endif