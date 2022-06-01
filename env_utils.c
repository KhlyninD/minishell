/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:05:18 by mvenmo            #+#    #+#             */
/*   Updated: 2022/04/11 15:59:50 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_getenv_p(const char *var)
{
	char	**array;
	char	*var2;
	int		len;

	var2 = ft_strjoin(var, "=");
	len = ft_strlen(var2);
	array = g_mini.mini_env;
	while (*array)
	{
		if (!ft_strncmp(*array, var2, len) || !ft_strcmp(*array, var))
		{
			free(var2);
			return (array);
		}
		array++;
	}
	free(var2);
	return (NULL);
}

char	*ft_getenv(const char *var)
{
	char	**res;

	res = ft_getenv_p(var);
	if (res && ft_strchr(*res, '='))
		return (*res + ft_strlen(var) + 1);
	return (NULL);
}

char	*ft_getvar(const char *var)
{
	char	*res;

	res = ft_strdup(ft_getenv(var));
	if (!res)
		res = ft_strdup("");
	return (res);
}

char	*ft_setvar(const char *var, const char *value)
{
	char	**array;

	array = ft_getenv_p(var);
	if (!array)
		ft_insert_str_to_array(&g_mini.mini_env, ft_strjoin3(var, "=", value));
	else
	{
		free(*array);
		*array = ft_strjoin3(var, "=", value);
	}
	return (ft_getenv(var));
}
