/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:20:53 by mvenmo            #+#    #+#             */
/*   Updated: 2022/04/14 21:36:41 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_str_isnumeric(const char *str)
{
	char	*tmp;
	int		res;

	tmp = ft_itoa(ft_atoi(str));
	if (ft_strcmp(tmp, str))
		res = 0;
	else
		res = 1;
	free(tmp);
	return (res);
}

static void	error_msg(char *name, char *arg, char *error)
{
	char	*tmp;

	tmp = ft_strjoin3(name, arg, error);
	ft_putendl_fd(tmp, 2);
	free(tmp);
}

int	ft_builtin_exit(char **argv)
{
	int		num;

	num = 0;
	if (g_mini.pid)
		ft_putendl_fd("exit", 2);
	if (argv[0])
	{
		if (!ft_str_isnumeric(argv[0]))
		{
			num = 255;
			error_msg("minishell: exit: ", argv[0],
				": numeric argument required");
		}
		else
		{
			num = ft_atoi(argv[0]);
			if (argv[1])
				return (err_msg_custom(1, "minishell: exit",
						"too many arguments"));
		}
	}
	g_mini.stop = 1;
	return (num);
}

// There are four types of exit, each write exit in terminal:
// exit : exit and set exit status to 0;
// exit (num) : exit and set exit status to num
// exit (num alpha) : exit and set exit status to 255 + error message
// exit (num) (num) (num) : doesn't exit, set exit status to 1 + error message

int	ft_export_checkargs(char **argv)
{
	int	i;
	int	res;

	argv--;
	res = 0;
	while (*++argv)
	{
		i = -1;
		while ((*argv)[++i] && ((*argv)[i] != '=' || i == 0))
		{
			if ((!ft_isalpha(*argv[0]) && *argv[0] != '_')
				|| (!ft_isalnum((*argv)[i]) && (*argv)[i] != '_'))
			{
				error_msg("minishell: export: `", *argv,
					"': not a valid identifier");
				res = 1;
				break ;
			}
		}
	}
	return (res);
}
