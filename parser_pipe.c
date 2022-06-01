/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjhin <mjhin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 10:38:51 by mjhin             #+#    #+#             */
/*   Updated: 2022/04/13 15:27:33 by mjhin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	position_pipe(int i)
{
	int	quote;

	quote = 0;
	while (g_mini.input_str[i])
	{
		quote = is_closed_quote(g_mini.input_str[i], quote);
		if (g_mini.input_str[i] == '|' && !quote)
			return (i);
		i++;
	}
	return (i);
}

static int	add_cmd_list(int start, int end)
{
	t_pip	*el;
	char	*str;

	el = el_new(NULL, NULL, NULL, NULL);
	if (!el)
		return (1);
	str = ft_substr(g_mini.input_str, start, end - start);
	if (!str)
		return (list_clear(el));
	el->cmd = ft_strtrim(str, " \t");
	free(str);
	if (!el->cmd)
		return (list_clear(el));
	lstadd_back(el);
	return (0);
}

int	parser_pipe(void)
{
	int	end;
	int	start;

	end = 0;
	start = 0;
	while (g_mini.input_str[end])
	{
		end = position_pipe(end);
		if (add_cmd_list(start, end))
		{
			list_clear(g_mini.head_pip);
			ft_putendl_fd("error malloc", 2);
			return (1);
		}
		if (g_mini.input_str[end])
			end++;
		start = end;
	}
	return (0);
}
