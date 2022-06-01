/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjhin <mjhin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:26:54 by mjhin             #+#    #+#             */
/*   Updated: 2022/04/14 11:54:00 by mjhin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_closed_quote(char c, int quote)
{
	if (c == '"')
	{
		if (!quote)
			return (2);
		else if (quote == 2)
			return (0);
	}
	else if (c == '\'')
	{
		if (!quote)
			return (1);
		else if (quote == 1)
			return (0);
	}
	return (quote);
}

int	is_separator(char *str, int flag)
{
	if ((str[0] == ' ' || str[0] == '<' || str[0] == '>' || str[0] == '\t')
		&& flag == 1)
		return (1);
	if (flag == 2)
	{
		if (!ft_strncmp(str, ">>", 2))
			return (2);
		else if (!ft_strncmp(str, "<<", 2))
			return (1);
		else if (!ft_strncmp(str, ">", 1))
			return (2);
		else if (!ft_strncmp(str, "<", 1))
			return (1);
	}
	if (flag == 3)
	{
		if (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "<<", 2))
			return (2);
		if (!ft_strncmp(str, "<>", 2) || !ft_strncmp(str, ">|", 2))
			return (2);
		if (!ft_strncmp(str, ">", 1) || !ft_strncmp(str, "<", 1))
			return (1);
	}
	return (0);
}

char	**add_mass(char **mass, char *str)
{
	int		n;
	char	**mass_c;

	if (!str)
		return (NULL);
	n = 0;
	while (mass && mass[n])
		n++;
	mass_c = malloc(sizeof(char *) * (n + 2));
	if (!mass_c)
		return (NULL);
	n = 0;
	while (mass && mass[n])
	{
		mass_c[n] = ft_strdup(mass[n]);
		n++;
	}
	if (mass)
		free_str_array(mass);
	mass_c[n] = str;
	mass_c[n + 1] = NULL;
	return (mass_c);
}

void	ft_free_str(char *s)
{
	if (s)
		free(s);
	s = NULL;
}

int	replace_str(int start, int end, t_pip *el, const char *str)
{
	char	*str1;
	char	*str2;

	str1 = ft_substr(el->cmd, 0, start);
	if (!str1 || !str)
		return (-1);
	start = ft_strlen(str1) + ft_strlen(str);
	str2 = ft_substr(el->cmd, end, ft_strlen(el->cmd) - end);
	ft_free_str(el->cmd);
	el->cmd = ft_strjoin3 (str1, str, str2);
	ft_free_str(str1);
	ft_free_str(str2);
	if (!el->cmd)
		return (-1);
	return (start);
}
