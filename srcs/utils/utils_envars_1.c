/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gscarama <gscarama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:58:27 by samunyan          #+#    #+#             */
/*   Updated: 2022/11/24 14:39:34 by gscarama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*str_arr_to_list(char *s[], void *(*init_content)(void *))
{
	size_t	i;
	t_list	*list;
	t_list	*new;

	list = NULL;
	i = 0;
	while (s[i])
	{
		new = ft_lstnew(NULL);
		if (!new)
		{
			ft_lstclear(&list, (void *)free_envar);
			return (NULL);
		}
		new->content = init_content(s[i]);
		if (!new->content)
		{
			ft_lstclear(&list, (void *)free_envar);
			return (NULL);
		}
		ft_lstadd_back(&list, new);
		i++;
	}
	return (list);
}

char	**list_to_str_arr(t_list *list, void *(format_string)(void *))
{
	size_t	i;
	char	**arr;

	i = ft_lstsize(list);
	arr = ft_malloc(sizeof(char *) * (i + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (list)
	{
		arr[i] = format_string(list->content);
		if (!arr[i])
		{
			ft_free_arr((void *)arr);
			return (NULL);
		}
		list = list->next;
		i++;
	}
	return (arr);
}

void	*envar_to_str(void *envar)
{
	char	*ret;
	t_envar	*cast;

	cast = (t_envar *)envar;
	ret = ft_strjoin(cast->name, "=");
	if (!ret)
		return (NULL);
	if (cast->value)
		ft_strappend(&ret, cast->value);
	return (ret);
}

void	*str_to_envar(void *s)
{
	t_envar	*var;

	var = ft_malloc(sizeof(t_envar));
	if (!var)
		return (NULL);
	if (ft_strchr(s, '='))
	{
		var->name = ft_strndup(s, ft_strchr(s, '=') - (char *)s);
		var->value = ft_strdup(ft_strchr(s, '=') + 1);
	}
	else
	{
		var->name = ft_strdup(s);
		var->value = NULL;
	}
	if (!var->name || (ft_strchr(s, '=') && !var->value))
	{
		free_envar(var);
		return (NULL);
	}
	return (var);
}
