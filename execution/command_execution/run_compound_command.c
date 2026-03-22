/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_compound_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:11:13 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/22 16:51:44 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	manage_pipe_ends_in_parent(t_subshell_resources *subshell_resources)
{
	if (subshell_resources->pid_node->child_nbr != 1)
	{
		close(subshell_resources->pipe_node->pipe[0]);
		if (subshell_resources->pid_node->next != NULL)
		{
			subshell_resources->pipe_node = subshell_resources->pipe_node->next;
			close(subshell_resources->pipe_node->pipe[1]);
		}
	}
	else
		close(subshell_resources->pipe_node->pipe[1]);
	return ;
}

static void	go_to_next_nodes(t_subshell_resources *subshell_resources)
{
	subshell_resources->pid_node = subshell_resources->pid_node->next;
	subshell_resources->command_node = subshell_resources->command_node->next;
	return ;
}

static void	free_lists(t_subshell_resources *subshell_resources)
{
	free_pipe_list(subshell_resources->pipe_list);
	free_pid_list(subshell_resources->pid_list);
	return ;
}

void	run_compound_command(t_exec_resources *exec_resources,
	t_prompt_resources *prompt_resources)
{
	t_subshell_resources	subshell_resources;

	if (create_pipe_and_pib_lists(&subshell_resources,
			count_commands(exec_resources->command_list)) != 0)
	{
		ft_dprintf(2, "minishell: fatal error occurred \
			while managing a pipe chain\n");
		return ;
	}
	subshell_resources.command_node = exec_resources->command_list;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (subshell_resources.command_node != NULL)
	{
		if (create_subshell(&subshell_resources, exec_resources,
				prompt_resources) != 0)
			return ;
		manage_pipe_ends_in_parent(&subshell_resources);
		go_to_next_nodes(&subshell_resources);
	}
	exec_resources->curr_exit_status
		= wait_for_all_children(subshell_resources.pid_list);
	init_signals();
	free_lists(&subshell_resources);
	return ;
}
