/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:10:45 by mvenmo            #+#    #+#             */
/*   Updated: 2022/04/14 14:50:07 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	warn_msg(const int n, const char *delimiter)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp3 = ft_itoa(n);
	tmp = ft_strjoin3("minishell: warning: here-document at line ",
			tmp3, " delimited by end-of-file (wanted `");
	tmp2 = ft_strjoin3(tmp, delimiter, "')");
	ft_putendl_fd(tmp2, 1);
	free(tmp);
	free(tmp2);
	free(tmp3);
}

static void	ft_restore_history(t_list *list)
{
	while (list)
	{
		add_history((const char *) list->content);
		list = list->next;
	}
}

static void	heredoc_reading(const char *delimeter, const int fd1, int *n)
{
	char	*tmp;

	g_mini.stop_heredoc = 0;
	clear_history();
	while (!g_mini.stop_heredoc)
	{
		(*n)++;
		tmp = readline("> ");
		if (!tmp)
			break ;
		if (!ft_strcmp(tmp, delimeter))
			g_mini.stop_heredoc = 1;
		else
			ft_putendl_fd(tmp, fd1);
		free(tmp);
	}
	ft_restore_history(g_mini.hst);
}

static int	here_doc_processing(char **array, int *n)
{
	int		fd[2];
	char	*tmp;

	if (pipe(fd) == -1)
		ft_exit(1, ft_strdup("minishell"));
	heredoc_reading(*array + 3, fd[1], n);
	close(fd[1]);
	if (g_mini.stop_heredoc == SIGINT)
	{
		dup2(g_mini.heredoc_f, 0);
		close(g_mini.heredoc_f);
		close(fd[0]);
		g_mini.stop_heredoc = -1;
		return (1);
	}
	if (g_mini.stop_heredoc == 0)
		warn_msg(*n, *array + 3);
	g_mini.stop_heredoc = -1;
	free(*array);
	tmp = ft_itoa(fd[0]);
	*array = ft_strjoin("<< ", tmp);
	free(tmp);
	return (0);
}

int	ft_here_doc(void)
{
	t_pip		*proc;
	char		**array;
	static int	n = 0;

	proc = g_mini.head_pip;
	while (proc)
	{
		array = proc->infile;
		if (array)
		{
			array--;
			while (*++array)
				if ((*array)[1] == '<')
					if (here_doc_processing(array, &n))
						return (1);
		}
		proc = proc->next;
	}
	g_mini.stop_heredoc = -1;
	return (0);
}
