/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_compound_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:11:13 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/21 15:40:36 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	run_compound_command(t_exec_resources *exec_resources, t_prompt_resources *prompt_resources)
{
	t_pipes	*pipe_list;
	t_pipes	*pipe_node;
	t_pids	*pid_list;
	t_pids	*pid_node;
	t_cmd	*command_node;

	if (create_pipe_and_pib_lists(&pipe_list, &pid_list, count_commands(exec_resources->command_list)) != 0)
	{
		exit_cleanup(exec_resources, prompt_resources);
		ft_dprintf(2, "minishell: fatal error occurred while managing a pipe chain\n");
		exit(EXIT_FAILURE);
	}
	pipe_node = pipe_list;
	pid_node = pid_list;
	command_node = exec_resources->command_list;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (command_node != NULL)
	{
		pid_node->pid = fork();
		if (pid_node->pid == -1)
		{
			ft_dprintf(2, "minishell: fork() failure in run_compound_command()\n");
			wait_for_all_children(pid_list);
			free_pipe_list(pipe_list);
			free_pid_list(pid_list);
			return ;
		}

		// Child
		if (pid_node->pid == 0)
		{
			//PIPES
			if (pid_node->child_nbr == 1)
			{
				if (command_node->next != NULL)
				{
					if (dup2(pipe_node->pipe[1], STDOUT_FILENO) == -1)
						exit_dup2_failure(pipe_list, pid_list, exec_resources, prompt_resources);
				}
				close_unused_fds(pipe_node);
			}
			else
			{
				if (dup2(pipe_node->pipe[0], STDIN_FILENO) == -1)
						exit_dup2_failure(pipe_list, pid_list, exec_resources, prompt_resources);
				if (pid_node->next != NULL)
				{
					if (dup2(pipe_node->next->pipe[1], STDOUT_FILENO) == -1)
						exit_dup2_failure(pipe_list, pid_list, exec_resources, prompt_resources);
					close_unused_fds(pipe_node->next);
				}
				close(pipe_node->pipe[0]);
			}
			free_pid_list(pid_list);
			if (command_node->redirs != NULL)
			{
				if (manage_redirections(command_node->redirs) != 0)
				{
					free_pipe_list(pipe_list);
					exit_cleanup(exec_resources, prompt_resources);
					exit(EXIT_FAILURE);
				}
			}
			run_command_in_subshell(command_node,
				exec_resources, prompt_resources, pipe_list);
		}

		// Parent
		if (pid_node->child_nbr == 1)
			close(pipe_node->pipe[1]);
		else
		{
			close(pipe_node->pipe[0]);
			if (pid_node->next != NULL)
			{
				pipe_node = pipe_node->next;
				close(pipe_node->pipe[1]);
			}
		}
		pid_node = pid_node->next;
		command_node = command_node->next;
	}
	exec_resources->curr_exit_status = wait_for_all_children(pid_list);
	init_signals();
	free_pipe_list(pipe_list);
	free_pid_list(pid_list);
	return ;
}
