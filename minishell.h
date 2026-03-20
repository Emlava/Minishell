/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:22:59 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/20 18:11:43 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "execution/execution.h"
# include "parsing/parsing.h"
# include <fcntl.h>

extern int	g_signal;

void	sigint_heredoc(int sig);
int		process_heredoc(t_redir *redir, t_exec_resources *res);
int		process_all_heredocs(t_cmd *cmds, t_exec_resources *res);
int		process_heredoc_helper(t_redir *redir, int fd[2],
			t_exec_resources *res);
void	write_line(int fd, char *line);
char	*join_args(char **argv);
int		process_all_heredocs_helper(t_redir *r, t_exec_resources *res);

#endif
