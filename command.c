/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:29:21 by mvenmo            #+#    #+#             */
/*   Updated: 2022/04/14 14:50:24 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_set_underscore(char **array)
{
	if (g_mini.head_pip->next || !array)
		return ;
	while (*array)
		array++;
	ft_setvar("_", *--array);
}

static void	start_all_forks(void)
{
	int		i;
	t_pip	*proc;

	i = 4;
	while (i-- > 0)
		g_mini.fd[i] = -1;
	proc = g_mini.head_pip;
	while (proc)
	{
		if (proc->next && pipe(&g_mini.fd[2]) == -1)
			ft_exit(1, ft_strdup("minishell"));
		g_mini.pid = fork();
		if (g_mini.pid == -1)
			ft_exit(1, ft_strdup("minishell"));
		if (g_mini.pid == 0)
			ft_start_process(proc);
		proc = proc->next;
		if (g_mini.fd[0] != -1)
			close(g_mini.fd[0]);
		if (g_mini.fd[1] != -1)
			close(g_mini.fd[1]);
		g_mini.fd[0] = g_mini.fd[2];
		g_mini.fd[1] = g_mini.fd[3];
	}
}

static void	run_with_forks(void)
{
	int		wstatus;
	t_pip	*proc;

	start_all_forks();
	waitpid(g_mini.pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		g_mini.last_command_res = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		g_mini.last_command_res = 128 + WTERMSIG(wstatus);
	proc = g_mini.head_pip->next;
	while (proc)
	{
		wait(NULL);
		proc = proc->next;
	}
}

int	run_commands(void)
{
	if (!g_mini.head_pip->next && g_mini.head_pip->args
		&& (!ft_strcmp(g_mini.head_pip->args[0], "exit")
			|| !ft_strcmp(g_mini.head_pip->args[0], "cd")
			|| !ft_strcmp(g_mini.head_pip->args[0], "export")
			|| !ft_strcmp(g_mini.head_pip->args[0], "unset")))
		run_if_builtin(g_mini.head_pip->args);
	else
		run_with_forks();
	ft_set_underscore(g_mini.head_pip->args);
	list_clear(g_mini.head_pip);
	return (0);
}
