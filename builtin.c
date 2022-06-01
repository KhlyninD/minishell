/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 08:31:31 by mvenmo            #+#    #+#             */
/*   Updated: 2022/04/14 20:45:53 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_builtin_echo(char **argv)
{
	int	new_line_at_the_end;

	new_line_at_the_end = 1;
	while (*argv && !ft_strncmp(*argv, "-n", 2))
	{
		argv++;
		new_line_at_the_end = 0;
	}
	while (*argv)
	{
		ft_putstr_fd(*argv++, 1);
		if (*argv)
			ft_putchar_fd(' ', 1);
	}
	if (new_line_at_the_end)
		ft_putchar_fd('\n', 1);
}

static void	ft_builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_getvar("PWD");
	ft_putendl_fd(pwd, 1);
	free(pwd);
}

static void	ft_builtin_unset(char **argv)
{
	char	**str_pointer;
	char	*str;

	while (*argv)
	{
		str_pointer = ft_getenv_p(*argv++);
		if (str_pointer)
		{
			str = ft_strdup(*str_pointer);
			ft_delete_from_array(g_mini.mini_env, str);
			free(str);
		}
	}
}

static void	ft_builtin_env(void)
{
	int	i;

	i = -1;
	while (g_mini.mini_env[++i])
		if (ft_strchr(g_mini.mini_env[i], '='))
			ft_putendl_fd(g_mini.mini_env[i], 1);
}

int	run_if_builtin(char **argv)
{
	int	exit_code;

	exit_code = 0;
	if (!ft_strcmp(argv[0], "echo"))
		ft_builtin_echo(&(argv[1]));
	else if (!ft_strcmp(argv[0], "cd"))
		exit_code = ft_builtin_cd(&argv[1]);
	else if (!ft_strcmp(argv[0], "pwd"))
		ft_builtin_pwd();
	else if (!ft_strcmp(argv[0], "export"))
		exit_code = ft_builtin_export(&(argv[1]));
	else if (!ft_strcmp(argv[0], "unset"))
		ft_builtin_unset(&argv[1]);
	else if (!ft_strcmp(argv[0], "env"))
		ft_builtin_env();
	else if (!ft_strcmp(argv[0], "exit"))
		exit_code = ft_builtin_exit(&argv[1]);
	else
		return (0);
	if (g_mini.pid == 0)
		exit(exit_code);
	g_mini.last_command_res = exit_code;
	return (1);
}
