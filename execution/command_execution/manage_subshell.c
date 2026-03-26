/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 16:29:48 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/22 16:39:01 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	manage_piping(t_subshell_resources *resources,
	t_exec_resources *exec_resources, t_prompt_resources *prompt_resources)
{
	if (resources->pid_node->child_nbr == 1)
	{
		if (resources->command_node->next != NULL)
		{
			if (dup2(resources->pipe_node->pipe[1], STDOUT_FILENO) == -1)
				exit_dup2_failure(resources, exec_resources, prompt_resources);
		}
		close_unused_fds(resources->pipe_node);
	}
	else
	{
		if (dup2(resources->pipe_node->pipe[0], STDIN_FILENO) == -1)
			exit_dup2_failure(resources, exec_resources, prompt_resources);
		if (resources->pid_node->next != NULL)
		{
			if (dup2(resources->pipe_node->next->pipe[1], STDOUT_FILENO) == -1)
				exit_dup2_failure(resources, exec_resources, prompt_resources);
			close_unused_fds(resources->pipe_node->next);
		}
		close(resources->pipe_node->pipe[0]);
	}
	return ;
}

static void	clean_and_exit_subshell(t_pipes *pipe_list,
	t_exec_resources *exec_resources, t_prompt_resources *prompt_resources)
{
	free_pipe_list(pipe_list);
	exit_cleanup(exec_resources, prompt_resources);
	exit(EXIT_FAILURE);
}

static void	run_command_in_subshell(t_cmd *command_node,
	t_exec_resources *exec_resources, t_prompt_resources *prompt_resources,
	t_pipes *pipe_list)
{
	int	exit_status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	exit_status = 0;
	if (command_node->builtin)
		exit_status = manage_builtin(command_node, exec_resources,
				prompt_resources);
	if (exec_resources->last_arg_present == true
		&& command_node->next == NULL)
		update_local_env_last_arg(exec_resources, command_node->argv);
	if (command_node->builtin == false)
		run_executable(command_node->argv, exec_resources,
			prompt_resources, pipe_list);
	exit_cleanup(exec_resources, prompt_resources);
	free_pipe_list(pipe_list);
	exit(exit_status);
}

int	create_subshell(t_subshell_resources *resources,
	t_exec_resources *exec_resources, t_prompt_resources *prompt_resources)
{
	resources->pid_node->pid = fork();
	if (resources->pid_node->pid == -1)
	{
		ft_dprintf(2, "minishell: fork() failure in run_compound_command()\n");
		wait_for_all_children(resources->pid_list);
		free_pipe_list(resources->pipe_list);
		free_pid_list(resources->pid_list);
		return (1);
	}
	if (resources->pid_node->pid == 0)
	{
		manage_piping(resources, exec_resources, prompt_resources);
		free_pid_list(resources->pid_list);
		if (resources->command_node->redirs != NULL)
		{
			if (manage_redirections(resources->command_node->redirs) != 0)
				clean_and_exit_subshell(resources->pipe_list, exec_resources,
					prompt_resources);
		}
		run_command_in_subshell(resources->command_node,
			exec_resources, prompt_resources, resources->pipe_list);
	}
	return (0);
}
