/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:40:49 by mjhin             #+#    #+#             */
/*   Updated: 2022/04/14 19:20:37 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_arg2(int start, int end, int quote, t_pip *el)
{
	char	*str;
	char	*str2;

	while (el->cmd[end] && (ft_isalnum(el->cmd[end]) || el->cmd[end] == '_'))
		end++;
	if (quote == 2 && el->cmd[end - 1] == '"')
		end--;
	str = ft_substr(el->cmd, start + 1, end - start - 1);
	if (!str)
		return (-1);
	str2 = ft_getvar(str);
	free(str);
	if (!str2)
		return (-1);
	end = replace_str(start, end, el, str2);
	free(str2);
	return (end);
}

static int	replace_arg(t_pip *el)
{
	int		quote;
	int		start;
	int		end;
	char	*str;

	end = 0;
	quote = 0;
	while (end >= 0 && el->cmd[end])
	{
		quote = is_closed_quote(el->cmd[end], quote);
		if (el->cmd[end] && el->cmd[end++] == '$' && quote != 1)
		{
			start = end;
			if (el->cmd[end] == '?')
			{
				str = ft_itoa(g_mini.last_command_res);
				end = replace_str(start - 1, end + 1, el, str);
				ft_free_str(str);
			}
			else if (el->cmd[end] != '\0' && el->cmd[end] != ' '
				&& el->cmd[end] != '\t' && el->cmd[end] != '~')
				end = replace_arg2(start - 1, end, quote, el);
		}
	}
	return (end);
}

int	check_redirect2(char *str)
{
	char	*err;
	char	*str_c;

	if (is_separator(str, 3))
	{
		str_c = ft_substr(str, 0, is_separator(str, 3));
		err = ft_strjoin3("syntax error near unexpected token '", str_c, "'");
		ft_free_str(str_c);
		if (!err)
		{
			ft_putendl_fd("error malloc", 2);
			return (1);
		}
		er_ms("", err, 258);
		free(err);
		return (1);
	}
	return (0);
}

static int	check_redirect(char *str)
{
	int		i;
	int		quote;

	i = -1;
	quote = 0;
	while (str[++i])
	{
		quote = is_closed_quote(str[i], quote);
		if (!quote && is_separator(str + i, 3))
		{
			i += is_separator(str + i, 3);
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (!str[i])
			{
				er_ms("syntax error near unexpected token ", "`newline'", 258);
				return (1);
			}
			else if (is_separator(str + i, 2) && check_redirect2(str + i))
				return (1);
		}
	}
	return (0);
}

int	parser(void)
{
	t_pip	*el;

	g_mini.head_pip = NULL;
	if (parser_pipe())
		return (1);
	el = g_mini.head_pip;
	while (el)
	{
		if (check_redirect(el->cmd))
		{
			list_clear(g_mini.head_pip);
			return (1);
		}
		if (replace_tild(el) < 0 || replace_arg(el) < 0 || parser_cmd(el))
		{
			ft_putendl_fd("error malloc", 2);
			list_clear(g_mini.head_pip);
			return (1);
		}
		el = el->next;
	}
	return (0);
}
