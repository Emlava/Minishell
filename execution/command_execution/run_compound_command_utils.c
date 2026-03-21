/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_compound_command_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elara-va <elara-va@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 15:36:44 by elara-va          #+#    #+#             */
/*   Updated: 2026/03/21 15:43:40 by elara-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_commands(t_cmd *command_list)
{
	int	command_count;

	command_count = 0;
	while (command_list != NULL)
	{
		command_count++;
		command_list = command_list->next;
	}
	return (command_count);
}

void	close_unused_fds(t_pipes *pipe_list)
{
	while (pipe_list)
	{
		close(pipe_list->pipe[0]);
		close(pipe_list->pipe[1]);
		pipe_list = pipe_list->next;
	}
	return ;
}

void	run_command_in_subshell(t_cmd *command_node,
	t_exec_resources *exec_resources, t_prompt_resources *prompt_resources,
	t_pipes *pipe_list)
{
	int	exit_status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
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

// Returns the exit status of the last child process.
int	wait_for_all_children(t_pids *pid_list)
{
	int	wstatus;

	while (pid_list != NULL && pid_list->pid != -1)
	{
		waitpid(pid_list->pid, &wstatus, 0);
		pid_list = pid_list->next;
	}
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else
	{
		if (WIFSIGNALED(wstatus))
		{
			if (WTERMSIG(wstatus) == SIGINT)
				write(2, "\n", 1);
			else if (WTERMSIG(wstatus) == SIGQUIT)
				ft_dprintf(2, "Quit (core dumped)\n");
		}
		return (WTERMSIG(wstatus) + 128);
	}
}

void	exit_dup2_failure(t_pipes *pipes, t_pids *pids,
	t_exec_resources *res, t_prompt_resources *prompt)
{
	free_pipe_list(pipes);
	free_pid_list(pids);
	exit_cleanup(res, prompt);
	ft_dprintf(2, "minishell: dup2() failure\n");
	exit(EXIT_FAILURE);
}
