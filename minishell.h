/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:20:34 by mvenmo            #+#    #+#             */
/*   Updated: 2022/04/14 20:46:44 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_pipes
{
	struct s_pipes	*prev;
	struct s_pipes	*next;
	char			**args;
	char			**infile;
	char			**outfile;
	char			*cmd;
}	t_pip;

typedef struct s_mini
{
	int		stop;
	t_pip	*head_pip;
	char	**mini_env;
	char	*input_str;
	t_list	*hst;
	pid_t	pid;
	int		fd[4];
	int		last_command_res;
	char	*prompt;
	int		stop_heredoc;
	int		heredoc_f;
}	t_mini;

extern t_mini	g_mini;

void	lstadd_back(t_pip *elem);
t_pip	*el_new(char **args, char *cmd, char **infile, char **outfile);
int		parser(void);
int		check_base(void);
int		run_commands(void);
void	free_str_array(char **array);
int		list_clear(t_pip *lst);
void	ft_exit(int n, char *name);
int		err_msg_custom(int status, char *command_name, char *err_msg);
int		er_ms(char *input, char *error_mess, int status);
void	rl_replace_line(const char *text, int clear_undo);
int		is_closed_quote(char c, int quote);
int		parser_pipe(void);
int		run_if_builtin(char **argv);
char	**ft_copy_str_array(char **array, char **copy);
char	**ft_insert_str_to_array(char ***array_pointer, char *str);
char	**ft_delete_from_array(char **array, const char *str);
void	ft_sort_str_array(char **array);
char	*ft_getenv(const char *var);
char	**ft_getenv_p(const char *var);
char	*ft_getvar(const char *var);
char	*ft_setvar(const char *var, const char *value);
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3);
char	**add_mass(char **mass, char *str);
int		parser_cmd(t_pip *el);
int		is_separator(char *str, int flag);
int		replace_str(int start, int end, t_pip *el, const char *str);
void	ft_pipes_and_files(t_pip *proc);
void	ft_start_process(t_pip *proc);
int		ft_builtin_cd(char **argv);
int		ft_builtin_export(char **argv);
int		ft_export_checkargs(char **argv);
char	*ft_getprompt_from_env(void);
void	ft_free_str(char *str);
char	*ft_getcwd(void);
int		ft_here_doc(void);
int		ft_builtin_exit(char **argv);
int		check_redirect2(char *str);
int		add_infile_outfile_list(int start, int end, t_pip *el, int op);
int		replace_tild(t_pip *el);

#endif
