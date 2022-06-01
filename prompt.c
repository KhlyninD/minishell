/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:20:13 by mvenmo            #+#    #+#             */
/*   Updated: 2022/04/14 22:12:42 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	er_ms(char *input, char *error_mess, int status)
{
	char	*str;

	str = ft_strjoin3("minishell: ", input, error_mess);
	ft_putendl_fd(str, 2);
	free(str);
	g_mini.last_command_res = status;
	return (-1);
}

static char	*ft_get_colors_from_env(void)
{
	char	*res;
	char	**array;
	int		i;

	res = NULL;
	if (ft_getenv("LS_COLORS"))
	{
		array = ft_split(ft_getenv("LS_COLORS"), ':');
		if (array)
		{
			i = -1;
			while (array[++i] && !res)
				if (!ft_strncmp(array[i], "di=", 3))
					res = ft_strjoin3("\e[", array[i] + 3, "m");
			free_str_array(array);
		}
	}
	if (!res)
		res = ft_strdup("\e[01;34m");
	return (res);
}

char	*ft_getcwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd && ft_getenv("PWD"))
		pwd = ft_getvar("PWD");
	if (!pwd)
		pwd = ft_strdup(".");
	return (pwd);
}

char	*ft_getprompt_from_env(void)
{
	char	*tmp;
	char	*pwd;
	char	*home;
	int		len;

	pwd = ft_getcwd();
	home = ft_getenv("HOME");
	if (home)
	{
		len = ft_strlen(home);
		if (ft_strnstr(pwd, home, len) == pwd)
		{
			tmp = pwd;
			pwd = ft_strjoin("~", &pwd[len]);
			free(tmp);
		}
	}
	ft_free_str(g_mini.prompt);
	tmp = ft_get_colors_from_env();
	g_mini.prompt = ft_strjoin3(tmp, pwd, "\e[0m$ ");
	free(pwd);
	free(tmp);
	return (g_mini.prompt);
}

void	ft_sort_str_array(char **array)
{
	char	**array_b;
	char	*tmp;

	array--;
	while (*++array)
	{
		array_b = array;
		while (*++array_b)
		{
			if (ft_strcmp(*array, *array_b) > 0)
			{
				tmp = *array;
				*array = *array_b;
				*array_b = tmp;
			}
		}
	}
}
