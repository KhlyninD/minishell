/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:20:53 by mvenmo            #+#    #+#             */
/*   Updated: 2022/04/14 22:10:18 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_oldpwd(char **dir)
{
	*dir = ft_getenv("OLDPWD");
	if (*dir)
		ft_putendl_fd(*dir, 1);
	return (*dir == NULL);
}

int	ft_builtin_cd(char **argv)
{
	char	*dir;
	char	*tmp;

	if (argv[0] && argv[1])
		return (err_msg_custom(2, "minishell: cd", "too many arguments"));
	dir = argv[0];
	if (!dir || !ft_strcmp(dir, "--"))
		dir = ft_getenv("HOME");
	if (!dir)
		return (err_msg_custom(1, "minishell: cd", "HOME not set"));
	if (!ft_strcmp(dir, "-") && ft_check_oldpwd(&dir))
		return (err_msg_custom(1, "minishell: cd", "OLDPWD not set"));
	if (chdir(dir) == -1)
	{
		tmp = ft_strjoin("minishell: cd: ", dir);
		perror(tmp);
		free(tmp);
		return (1);
	}
	if (ft_getenv("PWD"))
		ft_setvar("OLDPWD", ft_getenv("PWD"));
	dir = ft_getcwd();
	ft_setvar("PWD", dir);
	free(dir);
	return (0);
}

static void	ft_custom_print(char *var, char *value)
{
	ft_putstr_fd(var, 1);
	ft_putstr_fd("=\"", 1);
	ft_putstr_fd(value, 1);
	ft_putstr_fd("\"\n", 1);
}

static void	ft_b_export_show_list(void)
{
	char	**array;
	char	*tmp;
	char	*eqv_sign;
	int		i;

	array = ft_copy_str_array(g_mini.mini_env, NULL);
	ft_sort_str_array(array);
	i = -1;
	while (array[++i])
	{
		if (!ft_strncmp(array[i], "_=", 2))
			continue ;
		ft_putstr_fd("declare -x ", 1);
		if (!ft_strchr(array[i], '='))
		{
			ft_putendl_fd(array[i], 1);
			continue ;
		}
		eqv_sign = ft_strnstr(array[i], "=", ft_strlen(array[i]));
		tmp = ft_substr(array[i], 0, eqv_sign - array[i]);
		ft_custom_print(tmp, eqv_sign + 1);
		free(tmp);
	}
	free_str_array(array);
}

int	ft_builtin_export(char **argv)
{
	char	*tmp;
	char	*eqv_sign;

	if (*argv == NULL)
		ft_b_export_show_list();
	else if (ft_export_checkargs(argv))
		return (1);
	else
	{
		argv--;
		while (*++argv)
		{
			eqv_sign = ft_strnstr(*argv, "=", ft_strlen(*argv));
			tmp = ft_substr(*argv, 0, eqv_sign - *argv);
			if (ft_getenv_p(tmp))
			{
				if (eqv_sign)
					ft_setvar(tmp, eqv_sign + 1);
			}
			else
				ft_insert_str_to_array(&g_mini.mini_env, ft_strdup(*argv));
			free(tmp);
		}
	}
	return (0);
}
