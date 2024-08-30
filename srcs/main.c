/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:22:56 by samunyan          #+#    #+#             */
/*   Updated: 2022/12/08 10:41:06 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*g_envars;

void	msh(char *input)
{
	t_list	*tok_list;
	t_list	*cmd_list;

	tok_list = lexer(input);
	free(input);
	if (!tok_list)
	{
		update_exitcode(EXIT_FAILURE);
		return ;
	}
	cmd_list = parser(&tok_list);
	if (!cmd_list)
		return ;
	if (expander(cmd_list, g_envars) == -1)
	{
		update_exitcode(EXIT_FAILURE);
		ft_lstclear(&cmd_list, free_cmd);
		return ;
	}
	execute(cmd_list);
}

char	*get_input(void)
{
	char	*input;

	if (isatty(STDIN_FILENO))
		input = readline(PS1);
	else
	{
		input = get_next_line(STDIN_FILENO);
		if (input)
			input[ft_strlen(input) - 1] = '\0';
	}
	if (input && *input && isatty(STDIN_FILENO))
		add_history(input);
	return (input);
}

static int	finish(int exitcode)
{
	ft_lstclear(&g_envars, free_envar);
	if (isatty(STDIN_FILENO))
		rl_clear_history();
	if (errno == ENOMEM)
	{
		msh_error(strerror, errno, "readline");
		return (EXIT_FAILURE);
	}
	return (exitcode);
}

int	main(int ac, char *av[], char *env[])
{
	char	*input;
	char	*trim;

	(void)ac;
	(void)av;
	if (!init_envars_list(env, &g_envars))
		return (EXIT_FAILURE);
	while (true)
	{
		errno = 0;
		set_input_signals();
		input = get_input();
		if (!input)
			exit(finish(get_exitcode()));
		trim = ft_strtrim(input, " \t");
		free(input);
		if (!trim)
			exit(finish(EXIT_FAILURE));
		if (*trim)
			msh(trim);
		else
			free(trim);
	}
}
