/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hudescam <hudescam@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:22:59 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/20 13:42:33 by hudescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include "execution/execution.h"
#include "parsing/parsing.h"
#include <fcntl.h>

extern int	g_signal;

void	sigint_heredoc(int sig);
int	process_heredoc(t_redir *redir, t_exec_resources *res);
int	process_all_heredocs(t_cmd *cmds, t_exec_resources *res);

#endif
