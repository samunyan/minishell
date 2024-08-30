/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envars.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:55:09 by samunyan          #+#    #+#             */
/*   Updated: 2022/12/07 17:33:33 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVARS_H
# define ENVARS_H

# include	"minishell.h"

typedef struct s_envar
{
	char	*name;
	char	*value;
	int		n;
	int		export;
}	t_envar;

extern t_list	*g_envars;

t_list	*init_envars_list(char *env[], t_list **g_envars);
t_list	*str_arr_to_list(char *s[], void *(*init_content)(void *));
void	*str_to_envar(void *s);
char	**list_to_str_arr(t_list *list, void *(*format_string)(void *));
void	*envar_to_str(void *envar);

char	*msh_getenv(char *name);
t_envar	*get_t_envar(t_list *node);
t_list	*find_envar(char *name);
t_envar	*get_envar(char *name);
t_list	*add_envar(char *name_equal_value);
void	free_envar(void *var);

bool	update_shlvl(void);

bool	init_exitcode(void);
void	update_exitcode(int exitcode);
int		get_exitcode(void);

#endif