/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjhin <mjhin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:28:13 by mjhin             #+#    #+#             */
/*   Updated: 2022/04/12 11:00:14 by mjhin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pip	*el_new(char **args, char *cmd, char **infile, char **outfile)
{
	t_pip	*el;

	el = (t_pip *)malloc(sizeof(t_pip));
	if (!el)
		return (NULL);
	el->prev = NULL;
	el->next = NULL;
	el->args = args;
	el->infile = infile;
	el->outfile = outfile;
	el->cmd = cmd;
	return (el);
}

void	lstadd_back(t_pip *elem)
{
	t_pip	*el;

	if (elem)
	{
		if (!g_mini.head_pip)
		{
			g_mini.head_pip = elem;
		}
		else
		{
			el = g_mini.head_pip;
			while (el->next)
				el = el->next;
			el->next = elem;
			elem->prev = el;
		}
	}
}

int	list_clear(t_pip *lst)
{
	t_pip	*del;

	while (lst)
	{
		del = lst;
		lst = lst->next;
		free_str_array(del->args);
		free_str_array(del->infile);
		free_str_array(del->outfile);
		if (del->cmd)
			free(del->cmd);
		free(del);
		del = NULL;
	}
	return (1);
}
