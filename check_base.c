/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjhin <mjhin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:48:17 by mjhin             #+#    #+#             */
/*   Updated: 2022/04/14 20:45:09 by mjhin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_redirect_unic(char *str)
{
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	while (str[++i])
	{
		quote = is_closed_quote(str[i], quote);
		if (!ft_strncmp(str + i, ">|", 2) && !quote)
		{
			if (i != 0 && (str[i - 1] == '>' || str[i - 1] == '<'))
				continue ;
			str[++i] = ' ';
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (!str[i])
			{
				er_ms("", "syntax error near unexpected token `newline'", 258);
				return (1);
			}
		}
	}
	return (0);
}

static int	check_red_out_in2(int flag)
{
	if (flag)
		return (er_ms("", "syntax error near unexpected token `|'", 258));
	return (0);
}

static int	check_red_out_in(char *str)
{
	int	i;
	int	flag;
	int	quote;

	i = -1;
	flag = 0;
	quote = 0;
	while (str[++i])
	{
		quote = is_closed_quote(str[i], quote);
		if (!quote && str[i] == '|')
			return (check_red_out_in2(flag));
		else if (!quote && !flag && is_separator(str + i, 2))
		{
			flag = 1;
			i += is_separator(str + i, 3) - 1;
		}
		else if (!quote && flag && check_redirect2(str + i))
			return (1);
		else if (!quote && flag && str[i] != ' ' && str[i] != '\t')
			flag = 0;
	}
	return (0);
}

static int	check_pipe_and_quote(char *str)
{
	int	i;
	int	flag;
	int	quote;

	i = -1;
	flag = 1;
	quote = 0;
	while (str[++i])
	{
		quote = is_closed_quote(str[i], quote);
		if (!quote && str[i] != ' ' && str[i] != '\t' && str[i] != '|'
			&& !is_separator(str + i, 3))
			flag = 0;
		else if (str[i] == '|' && !quote)
		{
			if (flag || !str[i + 1])
				return (er_ms("", "syntax error near unexpected token '|'",
						258));
			flag = 1;
		}
	}
	if (quote)
		er_ms("", "miss quote", 2);
	return (quote);
}

int	check_base(void)
{
	char	*str;
	int		i;

	i = 0;
	while (g_mini.input_str[i] == ' ' || g_mini.input_str[i] == '\t')
		i++;
	if (!g_mini.input_str[i])
		return (1);
	str = ft_strtrim(g_mini.input_str, " \t");
	if (!str)
	{
		ft_putendl_fd("error malloc", 2);
		return (1);
	}
	free(g_mini.input_str);
	g_mini.input_str = str;
	if (check_red_out_in(g_mini.input_str)
		|| check_redirect_unic(g_mini.input_str)
		|| check_pipe_and_quote(g_mini.input_str))
		return (1);
	return (0);
}
