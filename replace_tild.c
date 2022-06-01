/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_tild.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjhin <mjhin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:06:56 by mjhin             #+#    #+#             */
/*   Updated: 2022/04/14 18:14:04 by mjhin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_tild(t_pip *el)
{
	int		quote;
	int		i;
	char	*str;

	i = -1;
	quote = 0;
	while (el->cmd[++i] && i > -1)
	{
		quote = is_closed_quote(el->cmd[i], quote);
		if (!quote && el->cmd[i] == '~')
		{
			if (!i || (i && (el->cmd[i - 1] == ' ' || el->cmd[i - 1] == '\t')))
			{
				if (el->cmd[i + 1] == ' ' || el->cmd[i + 1] == '\t'
					|| el->cmd[i + 1] == '/' || el->cmd[i + 1] == '\0')
				{
					str = ft_getvar("HOME");
					i = replace_str(i, i + 1, el, str) - 1;
					ft_free_str(str);
				}
			}
		}
	}
	return (i);
}
