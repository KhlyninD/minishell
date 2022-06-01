/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_infile_outfile_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjhin <mjhin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 15:34:23 by mjhin             #+#    #+#             */
/*   Updated: 2022/04/14 15:35:45 by mjhin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_infile_outfile_list3(char *str1, char *str2, int op, t_pip *el)
{
	int		flag;
	char	*str;

	str = ft_strjoin3(str1, " ", str2);
	ft_free_str(str1);
	ft_free_str(str2);
	flag = 0;
	if (op == 2)
	{
		el->outfile = add_mass(el->outfile, str);
		if (!el->outfile)
			flag = 1;
	}
	else
	{
		el->infile = add_mass(el->infile, str);
		if (!el->infile)
			flag = 1;
	}
	return (flag);
}

static int	add_infile_outfile_list2(int end, t_pip *el)
{
	int		quote;
	int		quote_c;

	quote = 0;
	quote_c = quote;
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

int	add_infile_outfile_list(int start, int end, t_pip *el, int op)
{
	char	*str1;
	char	*str2;

	if (el->cmd[end] == el->cmd[end - 1])
		end++;
	str1 = ft_substr(el->cmd, start, end - start);
	while (el->cmd[end] && (el->cmd[end] == ' ' || el->cmd[end] == '\t'))
		end++;
	start = end;
	end = add_infile_outfile_list2(end, el);
	if (end < 0)
	{
		ft_free_str(str1);
		return (-10);
	}
	str2 = ft_substr(el->cmd, start, end - start);
	if (add_infile_outfile_list3(str1, str2, op, el))
		return (-10);
	return (end);
}
