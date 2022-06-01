/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:29:21 by mvenmo            #+#    #+#             */
/*   Updated: 2022/04/13 19:44:30 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exit_for_file_error(char *filename)
{
	ft_putstr_fd("minishell: ", 2);
	ft_exit(1, ft_strdup(filename));
}

static void	ft_move_descriptor(int from, int to)
{
	dup2(from, to);
	close(from);
}

static void	ft_open_infiles(t_pip	*proc)
{
	int		f;
	char	**filename;

	if (proc->prev)
		close(g_mini.fd[0]);
	filename = proc->infile;
	while (*filename)
	{
		if ((*filename)[1] == '<')
			f = ft_atoi(*filename + 3);
		else
			f = open(*filename + 2, O_RDONLY);
		if (f == -1)
			ft_exit_for_file_error(*filename + 2);
		if (*++filename)
			close(f);
	}
	ft_move_descriptor(f, 0);
}

static void	ft_open_outfiles(t_pip	*proc)
{
	int		f;
	char	**filename;

	if (proc->next)
		close(g_mini.fd[3]);
	filename = proc->outfile;
	while (*filename)
	{
		if ((*filename)[1] == '>')
			f = open(*filename + 3, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			f = open(*filename + 2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (f == -1)
			ft_exit_for_file_error(*filename + 2 + ((*filename)[1] == '>'));
		if (*++filename)
			close(f);
	}
	ft_move_descriptor(f, 1);
}

void	ft_pipes_and_files(t_pip *proc)
{
	if (proc->prev)
		close(g_mini.fd[1]);
	if (proc->next)
		close(g_mini.fd[2]);
	if (proc->infile)
		ft_open_infiles(proc);
	else if (proc->prev)
		ft_move_descriptor(g_mini.fd[0], 0);
	if (proc->outfile)
		ft_open_outfiles(proc);
	else if (proc->next)
		ft_move_descriptor(g_mini.fd[3], 1);
}
