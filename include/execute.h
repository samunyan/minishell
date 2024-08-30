/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:23:29 by samunyan          #+#    #+#             */
/*   Updated: 2022/12/07 17:36:17 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
# include <sys/wait.h>
# include  <sys/stat.h>

# define READ	0
# define WRITE	1

typedef struct s_cmd	t_cmd;
typedef struct s_redir	t_redir;

// Utils to get the bin path for the command
int		get_bin_path_for_cmd(char *cmd, char **bin_path);
char	**get_bin_paths(void);

// Redirecting
int		redir_in(t_redir *redir, int *new_fd_is_set);
int		redir_out(t_redir *redir, int *new_fd_is_set);
int		set_io_piped_command(t_cmd *cmd, int **pipes);
int		set_io_simple_command(t_cmd *cmd, int saved_io[2]);

// Utils for piping and redirecting
void	close_pipes(int **pipes_fd);
int		**create_pipes(int n_cmds);
int		dup2_and_close_oldfd(int oldfd, int newfd);
void	close_stdio(void);

// Main functions for executing
void	execute(t_list *cmd_list);
void	do_piped_command(t_cmd *cmd, char **envp, int **pipes);
void	do_simple_command(t_list *cmd_list, char **envp);
void	do_pipeline(t_list *cmd_list, char **envp);
int		execute_simple_command(t_cmd *cmd, char **envp);
int		execute_builtin(t_cmd *cmd, char **envp);
int		execute_builtin_by_parent(t_cmd *cmd, char **envp, int *saved_io);

// Utils for executing
int		get_exitcode_from_child(int wstatus);
void	clear_cmd_list_except(t_list **cmd_list, void *content);

// Utils for builtins
bool	is_builtin(t_cmd *cmd);
bool	cmd_is_valid_builtin(t_cmd *cmd);

#endif
