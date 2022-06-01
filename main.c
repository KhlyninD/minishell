/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjhin <mjhin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:20:13 by mvenmo            #+#    #+#             */
/*   Updated: 2022/04/14 18:05:50 by mjhin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	g_mini;				

void	ft_exit(int n, char *name)
{
	int	i;

	i = n < 0;
	if (n == -127)
		n = 127;
	if (n > 0)
	{
		if (i)
			err_msg_custom(n, name, "command not found");
		else
			perror(name);
		free(name);
		i = 4;
		while (i-- > 0)
			if (g_mini.fd[i] != -1)
				close(g_mini.fd[i]);
	}
	free(g_mini.prompt);
	free_str_array(g_mini.mini_env);
	ft_lstclear(&g_mini.hst, free);
	if (n > 0)
		exit(n);
	if (!g_mini.stop)
		ft_putendl_fd("exit", 2);
}

void	interactive_handler(int signum)
{
	if (signum == SIGINT)
	{
		if (g_mini.stop_heredoc == -1)
		{
			ft_putstr_fd("\n", 1);
			rl_replace_line("", 1);
			rl_on_new_line();
			rl_redisplay();
		}
		if (g_mini.stop_heredoc == 0)
		{
			ft_putstr_fd("\n", 1);
			g_mini.stop_heredoc = SIGINT;
			g_mini.heredoc_f = dup(0);
			close(0);
		}
	}
}

void	run_handler(int signum)
{
	if (signum == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 1);
	else if (signum == SIGINT)
		ft_putstr_fd("\n", 1);
}

// +---------+------------------+-----------------+-----------------+
// |  mode   |          interactive mode          | run mode        |
// +---------+------------------+-----------------+-----------------+
// | signal  |   prompt mode    |  heredoc mode   | run mode        |
// +---------+------------------+-----------------+-----------------+
// |         | put endl,        | put endl        | put endl        |
// | ctrl+c  | display prompt   | close stdin     |                 |
// |(SIGINT) | on a new line    | (stop heredoc)  |                 |
// +---------+------------------+-----------------+-----------------+
// | ctrl+\  |                                    | put "Quit"      |
// |(SIGQUIT)|           do nothing               | message         |
// +---------+------------------+-----------------+-----------------+
//
// ctrl+d puts EOF-symbol (^D) in stdin to end input 

void	ft_init(int argc, char **argv, char **envp)
{
	char		*tmp;
	extern int	rl_catch_signals;

	if (argc != 1)
		exit(1 + 0 * write(2, "Usage: ./minishell\n", 19));
	if (signal(SIGINT, interactive_handler) == SIG_ERR
		|| signal(SIGQUIT, interactive_handler) == SIG_ERR)
		exit(errno);
	rl_catch_signals = 0;
	g_mini.stop_heredoc = -1;
	g_mini.hst = NULL;
	g_mini.last_command_res = 0;
	g_mini.mini_env = ft_copy_str_array(envp, NULL);
	g_mini.pid = 1;
	g_mini.prompt = NULL;
	ft_setvar("_", argv[0]);
	if (ft_getenv("SHLVL"))
	{
		tmp = ft_itoa(ft_atoi(ft_getenv("SHLVL")) + 1);
		ft_setvar("SHLVL", tmp);
		free(tmp);
	}
	else
		ft_setvar("SHLVL", "1");
}

int	main(int argc, char **argv, char **envp)
{
	ft_init(argc, argv, envp);
	g_mini.stop = 0;
	while (!g_mini.stop)
	{
		g_mini.input_str = readline(ft_getprompt_from_env());
		if (!g_mini.input_str)
			break ;
		if (*g_mini.input_str)
		{
			add_history(g_mini.input_str);
			ft_lstadd_back(&g_mini.hst, ft_lstnew(ft_strdup(g_mini.input_str)));
			if (!check_base() && !parser() && !ft_here_doc())
			{
				signal(SIGINT, run_handler);
				signal(SIGQUIT, run_handler);
				run_commands();
				signal(SIGINT, interactive_handler);
				signal(SIGQUIT, interactive_handler);
			}
		}
		free(g_mini.input_str);
	}
	ft_exit(0, NULL);
	return (g_mini.last_command_res);
}
