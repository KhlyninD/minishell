/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjhin <mjhin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:22:17 by mjhin             #+#    #+#             */
/*   Updated: 2022/04/14 15:34:51 by mjhin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_args_list2(int end, t_pip *el)
{
	int		quote;
	int		quote_c;

	quote = 0;
	while (el->cmd[end])
	{
		quote_c = quote;
		quote = is_closed_quote(el->cmd[end], quote);
		if ((!quote_c && quote) || (quote_c && !quote))
		{
			if (replace_str(end, end + 1, el, "") < 0)
				return (-10);
			continue ;
		}
		if (is_separator(el->cmd + end, 1) == 1 && quote == 0)
			break ;
		end++;
	}
	return (end);
}

static int	add_args_list(int start, int end, t_pip *el)
{
	char	*str;

	end = add_args_list2(end, el);
	if (end < 0)
		return (-10);
	str = ft_substr(el->cmd, start, end - start);
	el->args = add_mass(el->args, str);
	if (!el->args)
	{
		ft_free_str(str);
		return (-10);
	}
	return (end);
}

int	parser_cmd(t_pip *el)
{
	int		end;
	int		start;
	int		op;

	end = 0;
	while (el->cmd[end])
	{
		while (el->cmd[end] == ' ' || el->cmd[end] == '\t')
			end++;
		start = end;
		op = is_separator(el->cmd + end, 2);
		if (el->cmd[end] && op)
			end = add_infile_outfile_list(start, ++end, el, op);
		else
			end = add_args_list(start, end, el);
		if (end < 0)
			return (1);
	}
	return (0);
}
