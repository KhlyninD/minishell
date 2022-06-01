/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:29:21 by mvenmo            #+#    #+#             */
/*   Updated: 2022/04/14 18:27:38 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_path(void)
{
	char	**path;

	path = ft_split(ft_getenv("PATH"), ':');
	if (!path)
	{
		path = malloc(sizeof(*path) * 2);
		if (!path)
			return (NULL);
		path[0] = ft_getcwd();
		path[1] = NULL;
	}
	return (path);
}

static int	ft_try_start(char *path, char **args)
{
	char		*cmd;
	struct stat	statbuf;

	if (path)
		cmd = ft_strjoin3(path, "/", args[0]);
	else
		cmd = ft_strdup(args[0]);
	if (access(cmd, F_OK) == 0)
	{
		ft_setvar("_", cmd);
		execve(cmd, args, g_mini.mini_env);
		stat(cmd, &statbuf);
		if (S_ISDIR(statbuf.st_mode))
			errno = EISDIR;
		free(cmd);
		return (1);
	}
	free(cmd);
	return (0);
}

static void	ft_exec_file(t_pip *proc)
{
	char	*buf;
	int		exit_code;

	if (proc->args[0][0] != '/')
		buf = ft_getcwd();
	else
		buf = NULL;
	exit_code = 127;
	if (ft_try_start(buf, proc->args))
		exit_code = 126;
	if (buf)
		free(buf);
	ft_exit(exit_code, ft_strjoin("minishell: ", proc->args[0]));
}

int	err_msg_custom(int status, char *command_name, char *err_msg)
{
	char	*str;

	str = ft_strjoin3(command_name, ": ", err_msg);
	ft_putendl_fd(str, 2);
	free(str);
	return (status);
}

void	ft_start_process(t_pip *proc)
{
	char	**path;
	int		i;
	int		exit_code;

	ft_pipes_and_files(proc);
	if (!proc->args)
		exit(0);
	if (ft_strchr(proc->args[0], '/'))
		ft_exec_file(proc);
	else
	{
		if (run_if_builtin(proc->args))
			return ;
		path = get_path();
		i = 0;
		while (path[i])
			if (ft_try_start(path[i++], proc->args))
				break ;
		exit_code = -127;
		if (path[i])
			exit_code = 126;
		free_str_array(path);
		ft_exit(exit_code, ft_strjoin("minishell: ", proc->args[0]));
	}
}

// If input has '/'
// [/ls, ./ls, ls/, ../ls, ../.././ls, ~/minishell/a.out],
// this is <file> execution - we should not check paths from $PATH,
// just do simple execve with file. On erron type:
// minishell: /a.out: No such file or directory

// If input has no '/'
// [ls, ~ls],
// this is <command> execution - we should not start it separately, because
// this is built-in command (just start built-in only) OR 
// this is external command - start only (!) with path from $PATH
// On error type:
// a.out: command not found
